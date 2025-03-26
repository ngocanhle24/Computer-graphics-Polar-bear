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

		PPM* image1 = new PPM(infile);
		PPM* image2 = new PPM(*image1);
		PPM* image3 = new PPM(*image1);
		PPM* image4 = new PPM(*image1);
		PPM* image5 = new PPM(*image1);
		PPM* image6 = new PPM(*image1);
		PPM* image7 = new PPM(*image1);
		PPM* image8 = new PPM(*image1);
		PPM* image9 = new PPM(*image1);
		PPM* image10 = new PPM(*image1);

		Graphics g;

		//g.applyFilter(*image1, "blur"); // blur image
		//image1->saveImageToFile(filename + "_blur.ppm");
		//g.applyFilter(*image2, "sharpen"); // sharpen image
		//image2->saveImageToFile(filename + "_sharpen.ppm");
		//g.applyFilter(*image3, "edgeDetect"); // detect edges
		//image3->saveImageToFile(filename + "_edgeDetect.ppm");
		//g.applyFilter(*image4, "emboss"); // emboss image
		//image4->saveImageToFile(filename + "_emboss.ppm");
		//g.applyFilter(*image5, "magic"); // detect edges (alternate)
		//image5->saveImageToFile(filename + "_magic.ppm");

		g.scaleImage(*image6, 0.75); // shrink image
		image6->saveImageToFile(filename + "_scaleDown.ppm");
		g.scaleImage(*image7, 1.75); // expand image
		image7->saveImageToFile(filename + "_scaleUp.ppm");
		//g.rotateImage(*image8, 145);// rotate image CCW
		//image8->saveImageToFile(filename + "_rotate.ppm");
		// rotate image CW
		//g.translateImage(*image9, 300, -100);// tranlate image right and down
		//g.translateImage(*image9, -150, 250);// translate image left and up
		//image9->saveImageToFile(filename + "_translate.ppm");
		// convert image to grayscale

		delete image1;
		delete image2;
		delete image3;
		delete image4;
		delete image5;
		delete image6;
		delete image7;
		delete image8;
		delete image9;
		delete image10;
	}
	catch (const char* err)
	{
		cout << err << endl;
	}

	return 0;
}