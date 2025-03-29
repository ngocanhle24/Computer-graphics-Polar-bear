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

		Graphics g;

		time_t start, end;

		/* create images */
		PPM* image0 = new PPM(infile); // original image
		PPM* image1 = new PPM(*image0);
		PPM* image2 = new PPM(*image0);
		PPM* image3 = new PPM(*image0);
		PPM* image4 = new PPM(*image0);
		PPM* image5 = new PPM(*image0);
		PPM* image6 = new PPM(*image0);
		PPM* image7 = new PPM(*image0);
		PPM* image8 = new PPM(*image0);
		PPM* image9 = new PPM(*image0);
		PPM* image10 = new PPM(*image0);
		PPM* image11 = new PPM(*image0);
		PPM* image12 = new PPM(*image0);
		PPM* image13 = new PPM(*image0);
		PPM* image14 = new PPM(*image0);

		/* test filters */
		g.applyFilter(*image1, "blur"); // blur image
		image1->saveImageToFile(filename + "_blur.ppm");
		g.applyFilter(*image2, "sharpen"); // sharpen image
		image2->saveImageToFile(filename + "_sharpen.ppm");
		g.applyFilter(*image3, "edgeDetect"); // detect edges
		image3->saveImageToFile(filename + "_edgeDetect.ppm");
		g.applyFilter(*image4, "emboss"); // emboss image
		image4->saveImageToFile(filename + "_emboss.ppm");
		g.applyFilter(*image5, "magic"); // randomly-created filter (alternate)
		image5->saveImageToFile(filename + "_magic.ppm");

		/* test scaling */
		g.scaleImage(*image6, 0.5); // shrink image
		image6->saveImageToFile(filename + "_scaleDown.ppm");
		g.scaleImage(*image7, 1.75); // expand image
		image7->saveImageToFile(filename + "_scaleUp.ppm");
		g.scaleImage(*image8, -1.5); // reverse image
		image8->saveImageToFile(filename + "_reverse.ppm");

		/* test rotation */
		g.rotateImage(*image9, -47.6); // rotate image CCW
		image9->saveImageToFile(filename + "_CCW_rotation.ppm");
		g.rotateImage(*image10, 156.6); // rotate image CW
		image10->saveImageToFile(filename + "_CW_roatation.ppm");

		/* test translation */
		g.translateImage(*image11, 300, -100);// tranlate image right and down
		image11->saveImageToFile(filename + "_translateRD.ppm");
		g.translateImage(*image12, -150, 250);// translate image left and up
		image12->saveImageToFile(filename + "_translateLU.ppm");

		/* test grayscale */
		g.makeGrayscale(*image13);//convert image to grayscale
		image13->saveImageToFile(filename + "_grayScale.ppm");

		/* test invertColor */
		g.invertColors(*image14);//convert image to grayscale
		image14->saveImageToFile(filename + "_invertColors.ppm");

		/* delete images */
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
		delete image11;
		delete image12;
		delete image13;
		delete image14;

	}
	catch (const char* err) {
		cout << err << endl;
	}

	return 0;
}