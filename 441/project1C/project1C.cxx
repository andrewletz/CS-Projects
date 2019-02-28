#include <iostream>
#include <algorithm>
#include <vtkDataSet.h>
#include <vtkImageData.h>
#include <vtkPNGWriter.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkPolyDataReader.h>
#include <vtkPoints.h>
#include <vtkUnsignedCharArray.h>
#include <vtkFloatArray.h>
#include <vtkCellArray.h>

double ceil_441(double f) {
	return ceil(f-0.00001);
}

double floor_441(double f) {
	return floor(f+0.00001);
}

vtkImageData *NewImage(int width, int height) {
	vtkImageData *img = vtkImageData::New();
	img->SetDimensions(width, height, 1);
	img->AllocateScalars(VTK_UNSIGNED_CHAR, 3);

	return img;
}

void WriteImage(vtkImageData *img, const char *filename) {
	std::string full_filename = filename;
	full_filename += ".png";
	vtkPNGWriter *writer = vtkPNGWriter::New();
	writer->SetInputData(img);
	writer->SetFileName(full_filename.c_str());
	writer->Write();
	writer->Delete();
}

class Screen {
	public:
		unsigned char *buffer;
		int width, height;

		// index = row * width + column
		bool setPixel(int x, int y, unsigned char color[3]) {
			// if the desired pixel is out of range, do nothing
			if (x < 0) return false;
			if (x >= this->width) return false;
			if (y < 0) return false;
			if (y >= this->height) return false;

			// need to multiply by 3 because the buffer stores the RGB values for each pixel in order
			int index = 3 * (y * this->width + x);
			this->buffer[index] = color[0];
			this->buffer[index + 1] = color[1];
			this->buffer[index + 2] = color[2];
			return true;
		}
};

enum TriangleType { UP, DOWN, BOTH };

class Triangle {
	public:
		/*
			How each kind of triangle should be sorted
			Going up triangle
						  /\ X[0], Y[0]
						 /  \
						/    \
			X[1], Y[1] /______\ X[2], Y[2]

			Going down triangle
			X[1], Y[1]	______  X[2], Y[2]
					   \      /
					    \    /
					     \  /
					      \/ X[0], Y[0]

			Ambigious triangle
			Top point: X[0], Y[0]
			Middle point: X[1], Y[1]
			Bottom point: X[2], Y[2]
		*/
		double X[3];
		double Y[3];
		unsigned char color[3];

		// returns the triangle type and organizes the vertices for rasterization
		TriangleType sortVertices() {
			// if no Y values are the same it isn't up or down
			if (Y[0] != Y[1] && Y[1] != Y[2] && Y[0] != Y[2]) {
				// order the vertices as top, middle and bottom
				int maxYidx = 0;
				int minYidx = 0;
				for (int i = 1; i < 3; i++) {
					if (Y[i] > Y[maxYidx]) {
						maxYidx = i;
					} else if (Y[i] < Y[minYidx]) {
						minYidx = i;
					}
				}

				// if our max isn't at 0, put it there
				if (maxYidx != 0) {
					std::swap(Y[0], Y[maxYidx]);
					std::swap(X[0], X[maxYidx]);
					// if we swapped we need to make sure we didn't move around the min idx
					if (minYidx == 0) minYidx = maxYidx; 
				}

				// if our min isn't at 2, put it there
				if (minYidx != 2) {
					std::swap(Y[2], Y[minYidx]);
					std::swap(X[2], X[minYidx]);
				}
				
				assert(Y[0] >= Y[1] && Y[1] >= Y[2]);
				return BOTH; 
			}

			//  Y[0] should always be the only unique Y value, so swap it if it isn't
			if (Y[0] == Y[1]) {
				std::swap(Y[0], Y[2]);
				std::swap(X[0], X[2]);
			} else if (Y[0] == Y[2]) {
				std::swap(Y[0], Y[1]);
				std::swap(X[0], X[1]);
			}

			// if our X's are on the wrong sides, swap them
			if (X[1] > X[2]) {
				std::swap(Y[1], Y[2]);
				std::swap(X[1], X[2]);
			}
			
			assert(X[1] <= X[2]);
			if (Y[0] > Y[1]) { // we have a "going up triangle"
				return UP;
			} else { // we have a "going down triangle"
				return DOWN;
			}
		}

		// split an ambigious triangle into an UP and DOWN triangle for easier rasterization
		void splitAndRasterize(Screen *screen) {
			double slope = (X[0] != X[2]) ? (Y[0] - Y[2]) / (X[0] - X[2]) : 0;
			double b = Y[0] - (slope * X[0]);

			// need to find the other X value at the center point of the triangle
			double x = (slope != 0) ? (Y[1] - b) / slope : X[2];

			// split the triangle and rasterize each half
			Triangle goingUp;
			goingUp.X[0] = this->X[0];
			goingUp.X[1] = this->X[1];
			goingUp.X[2] = x;
			goingUp.Y[0] = this->Y[0];
			goingUp.Y[1] = this->Y[1];
			goingUp.Y[2] = this->Y[1];
			goingUp.color[0] = this->color[0];
			goingUp.color[1] = this->color[1];
			goingUp.color[2] = this->color[2];
			goingUp.rasterize(screen);

			Triangle goingDown;
			goingDown.X[0] = this->X[2];
			goingDown.X[1] = this->X[1];
			goingDown.X[2] = x;
			goingDown.Y[0] = this->Y[2];
			goingDown.Y[1] = this->Y[1];
			goingDown.Y[2] = this->Y[1];
			goingDown.color[0] = this->color[0];
			goingDown.color[1] = this->color[1];
			goingDown.color[2] = this->color[2];
			goingDown.rasterize(screen);
		}

		// called by other rasterization functions to draw a going up/going down triangle to the screen
		void rasterizeTriangle(Screen *screen, int rowMin, int rowMax) {
			double slopeLeft = (X[0] != X[1]) ? (Y[0] - Y[1]) / (X[0] - X[1]) : 0;
			double bLeft = Y[0] - (slopeLeft * X[0]);

			double slopeRight = (X[0] != X[2]) ? (Y[0] - Y[2]) / (X[0] - X[2]) : 0;
			double bRight = Y[0] - (slopeRight * X[0]);

			double leftEnd;
			double rightEnd;

			// for each scanline, find left and right ends of the triangle and fill it in
			for (int row = rowMin; row <= rowMax; row++) {
				leftEnd = (slopeLeft != 0) ? (row - bLeft) / slopeLeft : X[1];
				rightEnd = (slopeRight != 0) ? (row - bRight) / slopeRight : X[2];
				
				// cast row ends to proper values and fill in scan line from left to right
				for (int col = (int) ceil_441(leftEnd); col <= (int) floor_441(rightEnd); col++) {
					screen->setPixel(col, row, this->color);
				}
			}
		}

		// rasterize this triangle to the passed in Screen pointer
		void rasterize(Screen *screen) {
			TriangleType type = this->sortVertices();
			if (type == BOTH) return splitAndRasterize(screen);
			if (type == UP) return rasterizeTriangle(screen, (int) ceil_441(Y[1]), (int) floor_441(Y[0]));
			if (type == DOWN) return rasterizeTriangle(screen, (int) ceil_441(Y[0]), (int) floor_441(Y[1]));
		}

};

std::vector<Triangle> GetTriangles(void) {
	vtkPolyDataReader *rdr = vtkPolyDataReader::New();
    rdr->SetFileName("proj1c_geometry.vtk");
    cerr << "Reading" << endl;
    rdr->Update();
    if (rdr->GetOutput()->GetNumberOfCells() == 0)
    {
        cerr << "Unable to open file!!" << endl;
        exit(EXIT_FAILURE);
    }
    vtkPolyData *pd = rdr->GetOutput();
    int numTris = pd->GetNumberOfCells();
    vtkPoints *pts = pd->GetPoints();
    vtkCellArray *cells = pd->GetPolys();
    vtkFloatArray *colors = (vtkFloatArray *) pd->GetPointData()->GetArray("color_nodal");
    float *color_ptr = colors->GetPointer(0);
    std::vector<Triangle> tris(numTris);
    vtkIdType npts;
    vtkIdType *ptIds;
    int idx;
    for (idx = 0, cells->InitTraversal() ; cells->GetNextCell(npts, ptIds) ; idx++)
    {
        if (npts != 3)
        {
            cerr << "Non-triangles!! ???" << endl;
            exit(EXIT_FAILURE);
        }
        tris[idx].X[0] = pts->GetPoint(ptIds[0])[0];
        tris[idx].X[1] = pts->GetPoint(ptIds[1])[0];
        tris[idx].X[2] = pts->GetPoint(ptIds[2])[0];
        tris[idx].Y[0] = pts->GetPoint(ptIds[0])[1];
        tris[idx].Y[1] = pts->GetPoint(ptIds[1])[1];
        tris[idx].Y[2] = pts->GetPoint(ptIds[2])[1];
        tris[idx].color[0] = (unsigned char) color_ptr[4*ptIds[0]+0];
        tris[idx].color[1] = (unsigned char) color_ptr[4*ptIds[0]+1];
        tris[idx].color[2] = (unsigned char) color_ptr[4*ptIds[0]+2];
    }
    cerr << "Done reading" << endl;

    return tris;
}

int main() {
	// 1786 1344
	vtkImageData *image = NewImage(1786, 1344);
	unsigned char *buffer = (unsigned char *) image->GetScalarPointer(0,0,0);

	int npixels = 1786*1344;
	for (int i = 0 ; i < npixels*3 ; i++) buffer[i] = 0;

	std::vector<Triangle> triangles = GetTriangles();
	
	Screen screen;
	screen.buffer = buffer;
	screen.width = 1786;
	screen.height = 1344;

	for (int i = 0; i < triangles.size(); i++) {
		Triangle t = triangles[i];
		t.rasterize(&screen);
	}

	WriteImage(image, "NewGoDucks");
}
