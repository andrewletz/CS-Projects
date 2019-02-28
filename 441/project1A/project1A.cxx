#include <iostream>
#include <vtkDataSet.h>
#include <vtkImageData.h>
#include <vtkPNGWriter.h>
#include <vtkPointData.h>

using std::cerr;
using std::endl;

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


int main() {
	std::cerr << "In main!" << endl;
	vtkImageData *image = NewImage(1024, 1350);
	unsigned char *buffer;
	for (int y = 0; y < 1350; y++) {
		for (int x = 0; x < 1024; x++) {
			int strip = (int) (y / 50);
			buffer = (unsigned char *) image->GetScalarPointer(x, y, 0);
			int xmod3 = strip % 3;
			if (xmod3 == 0) {
				buffer[2] = 0;
			} else if (xmod3 == 1) {
				buffer[2] = 128;
			} else {
				buffer[2] = 255;
			}

			int xdiv3mod3 = (strip / 3) % 3;
			if (xdiv3mod3 == 0) {
				buffer[1] = 0;
			} else if (xdiv3mod3 == 1) {
				buffer[1] = 128;
			} else {
				buffer[1] = 255;
			}

			int xdiv9 = strip / 9;
			if (xdiv9 == 0) {
				buffer[0] = 0;
			} else if (xdiv9 == 1) {
				buffer[0] = 128;
			} else {
				buffer[0] = 255;
			}
		}
	}
	
	WriteImage(image, "proj1A");
}
