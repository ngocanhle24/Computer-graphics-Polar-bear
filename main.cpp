#include <iostream>
#include <fstream>
#include "Graphics.h"

int main()
{
	try {
		Graphics g; // instantiate context

		string filename = "Shahriar";

		ifstream infile(filename + ".ppm");
		if (!infile.is_open())
			throw "Error! File could not be opened.";

		/* create images */
		PPM* image = new PPM(infile); // original image
		PPM* temp = new PPM(*image); // copy image to temp

		/* test filters */
		*temp = g.applyFilter(*image, "blur"); // blur image
		temp->saveImageToFile(filename + "_blur.ppm");
		*temp = g.applyFilter(*image, "sharpen"); // sharpen image
		temp->saveImageToFile(filename + "_sharpen.ppm");
		*temp = g.applyFilter(*image, "edgeDetect"); // detect edges
		temp->saveImageToFile(filename + "_edgeDetect.ppm");
		*temp = g.applyFilter(*image, "emboss"); // emboss image
		temp->saveImageToFile(filename + "_emboss.ppm");
		*temp = g.applyFilter(*image, "magic"); // randomly-created filter (alternate)
		temp->saveImageToFile(filename + "_magic.ppm");

		/* test scaling */
		*temp = g.scaleImage(*image, 0.5); // shrink image
		temp->saveImageToFile(filename + "_scaleDown.ppm");
		*temp = g.scaleImage(*image, 1.75); // expand image
		temp->saveImageToFile(filename + "_scaleUp.ppm");
		*temp = g.scaleImage(*image, -1.0); // reverse image
		temp->saveImageToFile(filename + "_reverse.ppm");

		/* test rotation */
		*temp = g.rotateImage(*image, -45.0); // rotate image CCW
		temp->saveImageToFile(filename + "_CCW_rotation.ppm");
		*temp = g.rotateImage(*image, 45.0); // rotate image CW
		temp->saveImageToFile(filename + "_CW_roatation.ppm");

		/* test translation */
		*temp = g.translateImage(*image, 300, -100); // tranlate image right and down
		temp->saveImageToFile(filename + "_translateRD.ppm");
		*temp = g.translateImage(*image, -150, 250); // translate image left and up
		temp->saveImageToFile(filename + "_translateLU.ppm");

		/* test grayscale */
		*temp = g.makeGrayscale(*image); //convert image to grayscale
		temp->saveImageToFile(filename + "_grayScale.ppm");

		/* test color inversion */
		*temp = g.invertColors(*image); //convert image to grayscale
		temp->saveImageToFile(filename + "_invertColors.ppm");

		/* delete images */
		delete image;
		delete temp;

	}
	catch (const char* err) {
		cout << err << endl;
	}

	return 0;
}
