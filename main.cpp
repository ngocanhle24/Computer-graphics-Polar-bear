#include <iostream>
#include <fstream>

#include "Graphics.h"

int main()
{
	try {
		string filename = "Shahriar";

		ifstream infile(filename + ".ppm");
		if (!infile.is_open())
			throw "Error! File could not be opened.";

		/* create images */
		PPM* image1 = new PPM(infile);
		PPM* image2 = new PPM(move(*image1));
		PPM* image3 = new PPM(move(*image1));
		PPM* image4 = new PPM(move(*image1));
		PPM* image5 = new PPM(move(*image1));
		PPM* image6 = new PPM(move(*image1));
		PPM* image7 = new PPM(move(*image1));
		PPM* image8 = new PPM(move(*image1));

		Graphics g;

		/* test filters */
		g.applyFilter(*image1, "blur"); // blur image
		image1->saveImageToFile(filename + "_blur.ppm");
		g.applyFilter(*image2, "sharpen"); // sharpen image
		image2->saveImageToFile(filename + "_sharpen.ppm");
		g.applyFilter(*image3, "edgeDetect"); // detect edges
		image3->saveImageToFile(filename + "_edgeDetect.ppm");
		g.applyFilter(*image4, "emboss"); // emboss image
		image4->saveImageToFile(filename + "_emboss.ppm");
		g.applyFilter(*image5, "lapacian"); // detect edges (alternate)
		image5->saveImageToFile(filename + "_lapacian.ppm");

		/* test scaling */
		g.scaleImage(*image6, 0.2); // shrink image
		image6->saveImageToFile(filename + "_scaleDown.ppm");
		g.scaleImage(*image7, 2); // expand image
		image7->saveImageToFile(filename + "_scaleUp.ppm");
		g.scaleImage(*image8, -1); // reverse image
		image8->saveImageToFile(filename + "_reverse.ppm");

		/* test rotation */
		// rotate image CCW
		// rotate image CW

		/* test translation */
		// tranlate image right and down
		// translate image left and up

		/* test grayscale */
		// convert image to grayscale

		/* delete images */
		delete image1;
		delete image2;
		delete image3;
		delete image4;
		delete image5;
		delete image6;
		delete image7;
		delete image8;
	} catch (const char* err) {
		cout << err << endl;
	}

	return 0;
}