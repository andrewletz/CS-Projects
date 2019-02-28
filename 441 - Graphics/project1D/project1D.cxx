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
		double *zBuffer;
		int width, height;

		// index into zBuffer and return what is found
		double getZ(int x, int y) {
			if (x < 0 || x >= this->width || y < 0 || y >= this->height) return -1;
			return this->zBuffer[y * this->width + x];
		}

		// set the Z buffer at a particular row & column
		bool setZ(int x, int y, double z) {
			if (x < 0 || x >= this->width || y < 0 || y >= this->height) return false;
			this->zBuffer[y * this->width + x] = z;
			return true;
		}

		// index = row * width + column
		bool setPixel(int x, int y, unsigned char color[3]) {
			// if the desired pixel is out of range, do nothing
			if (x < 0 || x >= this->width || y < 0 || y >= this->height) return false;

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
						    /\ X[v2], Y[v2]
						   /  \
						  /    \
			X[v1], Y[v1] /______\ X[v3], Y[v3]

			Going down triangle
			X[v1], Y[v1]  ______  X[v3], Y[v3]
					     \      /
					      \    /
					       \  /
					        \/ X[v2], Y[v2]

			Ambigious triangle
			Top point: 		X[v1], Y[v1]
			Middle point: 	X[v2], Y[v2]
			Bottom point: 	X[v3], Y[v3]
		*/
		double X[3];
		double Y[3];
		double Z[3];
		double colors[3][3];

		int v1 = 0;
		int v2 = 1;
		int v3 = 2;

		// returns the triangle type and organizes the vertices for rasterization
		TriangleType sortVertices() {
			// if no Y values are the same it isn't up or down
			if (Y[0] != Y[1] && Y[1] != Y[2] && Y[0] != Y[2]) {
				// find v1, v2, v3
				for (int i = 0; i < 3; i++) {
					if (Y[i] > Y[v1]) {
						this->v1 = i;
					} else if (Y[i] < Y[v3]) {
						this->v3 = i;
					}
				}

				this->v2 = 3 - (v1 + v3); // v2 is the remaining vertex				
				assert(Y[v1] >= Y[v2] && Y[v2] >= Y[v3]);
				return BOTH; 
			}

			// find v2 (unique Y vertex)
			if (Y[v1] == Y[v2]) {
				std::swap(v2, v3);
			} else if (Y[v2] == Y[v3]) {
				std::swap(v2, v1);
			}

			// make sure the lowest X value is associated with v1
			if (X[v1] > X[v3]) std::swap(v1, v3);

			assert(X[v1] <= X[v3]);
			if (Y[v2] > Y[v1]) { // we have a "going up triangle"
				return UP;
			} else { // we have a "going down triangle"
				return DOWN;
			}
		}

		// split an ambigious triangle into an UP and DOWN triangle for easier rasterization
		void splitAndRasterize(Screen *screen) {
			double slope = (X[v1] != X[v3]) ? (Y[v1] - Y[v3]) / (X[v1] - X[v3]) : 0;
			double b = Y[v1] - (slope * X[v1]);

			// need to find the other X value at the center point of the triangle
			double otherX = (slope != 0) ? (Y[v2] - b) / slope : X[v3];

			// used for interpolation of new vertex's color
			double proportion = (Y[v2] - Y[v1]) / (Y[v3] - Y[v1]);

			// split the triangle and rasterize each half
			Triangle goingUp;
			goingUp.X[0] = this->X[v1];
			goingUp.X[1] = this->X[v2];
			goingUp.X[2] = otherX;
			goingUp.Y[0] = this->Y[v1];
			goingUp.Y[1] = this->Y[v2];
			goingUp.Y[2] = this->Y[v2];
			goingUp.Z[0] = this->Z[v1];
			goingUp.Z[1] = this->Z[v2];

			// first copy the unchanging colors from the corresponding vertices
			std::copy(&this->colors[v1][0], &this->colors[v1][0] + 3, &goingUp.colors[0][0]);
			std::copy(&this->colors[v2][0], &this->colors[v2][0] + 3, &goingUp.colors[1][0]);

			// interpolate color for the final vertex
			goingUp.colors[2][0] = colors[v1][0] + proportion * (colors[v3][0] - colors[v1][0]);
			goingUp.colors[2][1] = colors[v1][1] + proportion * (colors[v3][1] - colors[v1][1]);
			goingUp.colors[2][2] = colors[v1][2] + proportion * (colors[v3][2] - colors[v1][2]);

			// interpolate final Z value
			goingUp.Z[2] = Z[v1] + proportion * (Z[v3] - Z[v1]);
			goingUp.rasterize(screen);

			// do all the same stuff for the bottom half of the split triangle
			Triangle goingDown;
			goingDown.X[0] = this->X[v3];
			goingDown.X[1] = this->X[v2];
			goingDown.X[2] = otherX;
			goingDown.Y[0] = this->Y[v3];
			goingDown.Y[1] = this->Y[v2];
			goingDown.Y[2] = this->Y[v2];
			goingDown.Z[0] = this->Z[v3];
			goingDown.Z[1] = this->Z[v2];
			std::copy(&this->colors[v3][0], &this->colors[v3][0] + 3, &goingDown.colors[0][0]);
			std::copy(&this->colors[v2][0], &this->colors[v2][0] + 3, &goingDown.colors[1][0]);
			goingDown.colors[2][0] = colors[v1][0] + proportion * (colors[v3][0] - colors[v1][0]);
			goingDown.colors[2][1] = colors[v1][1] + proportion * (colors[v3][1] - colors[v1][1]);
			goingDown.colors[2][2] = colors[v1][2] + proportion * (colors[v3][2] - colors[v1][2]);
			goingDown.Z[2] = Z[v1] + proportion * (Z[v3] - Z[v1]);
			goingDown.rasterize(screen);
		}

		// called by other rasterization functions to draw a going up/going down triangle to the screen
		void rasterizeTriangle(Screen *screen, int rowMin, int rowMax) {
			double slopeLeft = (X[v1] != X[v2]) ? (Y[v2] - Y[v1]) / (X[v2] - X[v1]) : 0;
			double bLeft = Y[v2] - (slopeLeft * X[v2]);

			double slopeRight = (X[v2] != X[v3]) ? (Y[v2] - Y[v3]) / (X[v2] - X[v3]) : 0;
			double bRight = Y[v2] - (slopeRight * X[v2]);

			double leftEnd;
			double leftEndColor[3];

			double rightEnd;
			double rightEndColor[3];

			double zLeft;
			double zRight;

			double proportion;

			// for each scanline, find left and right ends of the triangle and fill it in
			for (int row = rowMin; row <= rowMax; row++) {
				leftEnd = (slopeLeft != 0) ? (row - bLeft) / slopeLeft : X[v1];
				rightEnd = (slopeRight != 0) ? (row - bRight) / slopeRight : X[v3];

				// interpolate the left end color
				proportion = (row - Y[v1]) / (Y[v2] - Y[v1]);
				leftEndColor[0] = colors[v1][0] + proportion * (colors[v2][0] - colors[v1][0]);
				leftEndColor[1] = colors[v1][1] + proportion * (colors[v2][1] - colors[v1][1]);
				leftEndColor[2] = colors[v1][2] + proportion * (colors[v2][2] - colors[v1][2]);
				// interpolate zLeft
				zLeft = Z[v1] + proportion * (Z[v2] - Z[v1]);

				// interpolate the right end color
				proportion = (row - Y[v3]) / (Y[v2] - Y[v3]);
				rightEndColor[0] = colors[v3][0] + proportion * (colors[v2][0] - colors[v3][0]);
				rightEndColor[1] = colors[v3][1] + proportion * (colors[v2][1] - colors[v3][1]);
				rightEndColor[2] = colors[v3][2] + proportion * (colors[v2][2] - colors[v3][2]);
				// interpolate zRight
				zRight = Z[v3] + proportion * (Z[v2] - Z[v3]);

				double currentColor[3];
				double currentZ;
				// cast row ends to proper values and fill in scan line from left to right
				for (int col = (int) ceil_441(leftEnd); col <= (int) floor_441(rightEnd); col++) {
					proportion = (col - leftEnd) / (rightEnd - leftEnd);
					currentZ = zLeft + proportion * (zRight - zLeft); // interpolate currentZ first

					if (currentZ > screen->getZ(col, row)) {
						// interpolate the color for the current column based on the previously calculated values
						currentColor[0] = leftEndColor[0] + proportion * (rightEndColor[0] - leftEndColor[0]);
						currentColor[1] = leftEndColor[1] + proportion * (rightEndColor[1] - leftEndColor[1]);
						currentColor[2] = leftEndColor[2] + proportion * (rightEndColor[2] - leftEndColor[2]);
						
						unsigned char castedColor[3] = { 
							(unsigned char) ceil_441(currentColor[0] * 255), 
							(unsigned char) ceil_441(currentColor[1] * 255), 
							(unsigned char) ceil_441(currentColor[2] * 255) };

						screen->setPixel(col, row, castedColor);
						screen->setZ(col, row, currentZ);
					}
				}
			}
		}

		// rasterize this triangle to the passed in Screen pointer
		void rasterize(Screen *screen) {
			TriangleType type = this->sortVertices();
			if (type == BOTH) return splitAndRasterize(screen);
			if (type == UP) return rasterizeTriangle(screen, (int) ceil_441(Y[v1]), (int) floor_441(Y[v2]));
			if (type == DOWN) return rasterizeTriangle(screen, (int) ceil_441(Y[v2]), (int) floor_441(Y[v1]));
		}

};

std::vector<Triangle> GetTriangles(void) {
	vtkPolyDataReader *rdr = vtkPolyDataReader::New();
	rdr->SetFileName("proj1d_geometry.vtk");
	cerr << "Reading" << endl;
	rdr->Update();
	cerr << "Done reading" << endl;
	if (rdr->GetOutput()->GetNumberOfCells() == 0) {
		cerr << "Unable to open file!!" << endl;
		exit(EXIT_FAILURE);
	}
	vtkPolyData *pd = rdr->GetOutput();
	int numTris = pd->GetNumberOfCells();
	vtkPoints *pts = pd->GetPoints();
	vtkCellArray *cells = pd->GetPolys();
	vtkFloatArray *var = (vtkFloatArray *) pd->GetPointData()->GetArray("hardyglobal");
	float *color_ptr = var->GetPointer(0);
	std::vector<Triangle> tris(numTris);
	vtkIdType npts;
	vtkIdType *ptIds;
	int idx;
	for (idx = 0, cells->InitTraversal() ; cells->GetNextCell(npts, ptIds) ; idx++) {
		if (npts != 3) {
			cerr << "Non-triangles!! ???" << endl;
			exit(EXIT_FAILURE);
		}
		tris[idx].X[0] = pts->GetPoint(ptIds[0])[0];
		tris[idx].X[1] = pts->GetPoint(ptIds[1])[0];
		tris[idx].X[2] = pts->GetPoint(ptIds[2])[0];
		tris[idx].Y[0] = pts->GetPoint(ptIds[0])[1];
		tris[idx].Y[1] = pts->GetPoint(ptIds[1])[1];
		tris[idx].Y[2] = pts->GetPoint(ptIds[2])[1];
		tris[idx].Z[0] = pts->GetPoint(ptIds[0])[2];
		tris[idx].Z[1] = pts->GetPoint(ptIds[1])[2];
		tris[idx].Z[2] = pts->GetPoint(ptIds[2])[2];
		double mins[7] = { 1, 2, 2.5, 3, 3.5, 4, 5 };
		double maxs[7] = { 2, 2.5, 3, 3.5, 4, 5, 6 };
		unsigned char RGB[8][3] = { { 71, 71, 219 }, 
									{ 0, 0, 91 },
									{ 0, 255, 255 },
									{ 0, 128, 0 },
									{ 255, 255, 0 },
									{ 255, 96, 0 },
									{ 107, 0, 0 },
									{ 224, 76, 76 } 
								  };
		for (int j = 0 ; j < 3 ; j++) {
			float val = color_ptr[ptIds[j]];
			int r;
			for (r = 0 ; r < 7 ; r++) {
				if (mins[r] <= val && val < maxs[r])
					break;
			}
			if (r == 7) {
				cerr << "Could not interpolate color for " << val << endl;
				exit(EXIT_FAILURE);
			}
			double proportion = (val-mins[r]) / (maxs[r]-mins[r]);
			tris[idx].colors[j][0] = (RGB[r][0]+proportion*(RGB[r+1][0]-RGB[r][0]))/255.0;
			tris[idx].colors[j][1] = (RGB[r][1]+proportion*(RGB[r+1][1]-RGB[r][1]))/255.0;
			tris[idx].colors[j][2] = (RGB[r][2]+proportion*(RGB[r+1][2]-RGB[r][2]))/255.0;
		}
	}

	return tris;
}

int main() {
	// 1000 x 1000
	vtkImageData *image = NewImage(1000, 1000);
	unsigned char *buffer = (unsigned char *) image->GetScalarPointer(0,0,0);

	int npixels = 1000*1000;
	for (int i = 0 ; i < npixels*3 ; i++) buffer[i] = 0;

	std::vector<Triangle> triangles = GetTriangles();
	
	Screen screen;
	screen.buffer = buffer;
	screen.zBuffer = new double[npixels];
	for (int i = 0 ; i < npixels ; i++) screen.zBuffer[i] = -1;
	screen.width = 1000;
	screen.height = 1000;

	for (unsigned int i = 0; i < triangles.size(); i++) {
		Triangle t = triangles[i];
		t.rasterize(&screen);
	}

	WriteImage(image, "allTriangles");
}
