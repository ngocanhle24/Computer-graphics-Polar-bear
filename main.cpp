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

		///* test filters */
		Graphics::applyFilter(*image1, "blur"); // blur image
		Graphics::applyFilter(*image1, "blur"); // blur image
		Graphics::applyFilter(*image1, "blur"); // blur image
		Graphics::applyFilter(*image1, "blur"); // blur image
		image1->saveImageToFile(filename + "_blur.ppm");
		Graphics::applyFilter(*image2, "sharpen"); // sharpen image
		image2->saveImageToFile(filename + "_sharpen.ppm");
		Graphics::applyFilter(*image3, "edgeDetect"); // detect edges
		image3->saveImageToFile(filename + "_edgeDetect.ppm");
		Graphics::applyFilter(*image4, "emboss"); // emboss image
		image4->saveImageToFile(filename + "_emboss.ppm");
		Graphics::applyFilter(*image5, "magic"); // randomly-created filter (alternate)
		image5->saveImageToFile(filename + "_magic.ppm");

		/* test scaling */
		Graphics::scaleImage(*image6, 0.5); // shrink image
		image6->saveImageToFile(filename + "_scaleDown.ppm");
		Graphics::scaleImage(*image7, 1.75); // expand image
		image7->saveImageToFile(filename + "_scaleUp.ppm");
		Graphics::scaleImage(*image8, -1.5); // reverse image
		image8->saveImageToFile(filename + "_reverse.ppm");

		/* test rotation */
		Graphics::rotateImage(*image9, -47.6); // rotate image CCW
		image9->saveImageToFile(filename + "_CCW_rotation.ppm");
		Graphics::rotateImage(*image10, 156.6); // rotate image CW
		image10->saveImageToFile(filename + "_CW_roatation.ppm");

		/* test translation */
		Graphics::translateImage(*image11, 300, -100);// tranlate image right and down
		image11->saveImageToFile(filename + "_translateRD.ppm");
		Graphics::translateImage(*image12, -150, 250);// translate image left and up
		image12->saveImageToFile(filename + "_translateLU.ppm");

		/* test grayscale */
		Graphics::makeGrayscale(*image13);//convert image to grayscale
		image13->saveImageToFile(filename + "_grayScale.ppm");

		/* test invertColor */
		Graphics::invertColors(*image14);//convert image to grayscale
		image14->saveImageToFile(filename + "_invertColors.ppm");

		/* delete images */
		delete image0;
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
