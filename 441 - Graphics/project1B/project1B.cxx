#include <iostream>
#include <vtkDataSet.h>
#include <vtkImageData.h>
#include <vtkPNGWriter.h>
#include <vtkPointData.h>

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

class Triangle {
	public:
		double X[3];
		double Y[3];
		unsigned char color[3];

		int topLeftIndex = -1;
		int topRightIndex = -1;
		int bottomIndex = -1;

		// initializes instance variables to the right indices
		void findIndices() {
			this->topLeftIndex = 0;
			this->topRightIndex = 0;
			this->bottomIndex = 0;

			for (int i = 1; i < 3; i++) {
				if (Y[i] >= Y[topLeftIndex]) {
					if (X[i] <= X[topLeftIndex]) {
						this->topLeftIndex = i;
					} else {
						this->topRightIndex = i;
					}
				} else {
					this->bottomIndex = i;
				}
			}
		}

		// lowest row for scanline algorithm (returned as casted int)
		int rowMin() {
			double minY = Y[0];
			if (Y[1] < minY) minY = Y[1];
			if (Y[2] < minY) minY = Y[2];
			return (int) ceil_441(minY);
		}

		// highest row for scanline algorithm (returned as casted int)
		int rowMax() {
			double maxY = Y[0];
			if (Y[1] > maxY) maxY = Y[1];
			if (Y[2] > maxY) maxY = Y[2];
			return (int) floor_441(maxY);
		}

		// for a given row (y value), gives the left end of this triangle
		int leftEnd(int row) {
			if (this->topLeftIndex == -1) this->findIndices();
			if (X[topLeftIndex] == X[bottomIndex]) return X[topLeftIndex]; // don't want to divide by 0

			double slope = (X[bottomIndex] - X[topLeftIndex]) / (Y[bottomIndex] - Y[topLeftIndex]);
			double left = X[bottomIndex];
			for (int i = this->rowMin(); i < row; i++) {
				left += slope;
			}

			return (int) ceil_441(left);
		}

		// for a given row (y value), gives the right end of this triangle
		int rightEnd(int row) {
			if (this->topLeftIndex == -1) this->findIndices();
			if (X[topRightIndex] == X[bottomIndex]) return X[topRightIndex]; // don't want to divide by 0

			double slope = (X[bottomIndex] - X[topRightIndex]) / (Y[bottomIndex] - Y[topRightIndex]);
			double right = X[bottomIndex];
			for (int i = this->rowMin(); i < row; i++) {
				right += slope;
			}

			return (int) floor_441(right);
		}
};

class Screen {
	public:
		unsigned char *buffer;
		int width, height;

		// index = row * width + column
		bool setPixel(int x, int y, unsigned char color[3]) {
			// if the desired pixel is out of range, instead paint the closest edge pixel
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

std::vector<Triangle> GetTriangles(void) {
	std::vector<Triangle> rv(100);

	unsigned char colors[6][3] = { {255,128,0}, {255, 0, 127}, {0,204,204}, 
								   {76,153,0}, {255, 204, 204}, {204, 204, 0} };
	for (int i = 0 ; i < 100 ; i++) {
		int idxI = i%10;
		int posI = idxI*100;
		int idxJ = i/10;
		int posJ = idxJ*100;
		int firstPt = (i%3);
		rv[i].X[firstPt] = posI;
		if (i == 50) rv[i].X[firstPt] = -10;
		rv[i].Y[firstPt] = posJ+10*(idxJ+1);
		rv[i].X[(firstPt+1)%3] = posI+99;
		rv[i].Y[(firstPt+1)%3] = posJ+10*(idxJ+1);
		rv[i].X[(firstPt+2)%3] = posI+i;
		rv[i].Y[(firstPt+2)%3] = posJ;
		if (i == 5) rv[i].Y[(firstPt+2)%3] = -50;
		rv[i].color[0] = colors[i%6][0];
		rv[i].color[1] = colors[i%6][1];
		rv[i].color[2] = colors[i%6][2];
	}

	return rv;
}

int main() {
	vtkImageData *image = NewImage(1000, 1000);
	unsigned char *buffer = (unsigned char *) image->GetScalarPointer(0,0,0);

	int npixels = 1000*1000;
	for (int i = 0 ; i < npixels*3 ; i++) buffer[i] = 0;

	std::vector<Triangle> triangles = GetTriangles();
	
	Screen screen;
	screen.buffer = buffer;
	screen.width = 1000;
	screen.height = 1000;

	for (int i = 0; i < 100; i += 1) {
		Triangle t = triangles[i];
		t.findIndices();

		// Some debug statements if you are curious about triangle information
		// std::cout << "	[0] : (" << t.X[0] << ", " << t.Y[0] << ")\n";
		// std::cout << "	[1] : (" << t.X[1] << ", " << t.Y[1] << ")\n";
		// std::cout << "	[2] : (" << t.X[2] << ", " << t.Y[2] << ")\n";
		// std::cout << "	top left: " << t.topLeftIndex << ", top right: " << t.topRightIndex << ", bottom: " << t.bottomIndex << "\n";

		// for (int z = rowMin; z < rowMax; z++) {
		// 	std::cout << "		draw to row " << z << " (left end here is " << t.leftEnd(z) << " )" << "\n";
		// }
		// std::cout << std::endl;

		int rowMin = t.rowMin();
		int rowMax = t.rowMax();

		for (int row = rowMin; row <= rowMax; row++) {
			for (int col = t.leftEnd(row); col <= t.rightEnd(row); col++) {
				screen.setPixel(col, row, t.color);
			}
		}
	}

	WriteImage(image, "allTriangles");
}
