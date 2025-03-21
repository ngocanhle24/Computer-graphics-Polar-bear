#include <iostream>
#include <fstream>

#include "Graphics.h"

// void print(const PPM &image)
// {
// 	for (int i = 0; i < image.getHeight(); i++)
// 	{
// 		for (int j = 0; j < image.getWidth(); j++)
// 		{
// 			cout << image[i * image.getHeight() + j]["red"] << " " << image[i * image.getHeight() + j]["green"] << " " << image[i * image.getHeight() + j]["blue"] << " ";
// 		}
// 		cout << endl;
// 	}
// }

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

		g.scaleImage(*image6, 0.5); // shrink image
		image6->saveImageToFile(filename + "_scaleDown.ppm");
		g.scaleImage(*image7, 2); // expand image
		image7->saveImageToFile(filename + "_scaleUp.ppm");
		// rotate image CCW
		// rotate image CW
		// tranlate image right and down
		// translate image left and up
		// convert image to grayscale

		delete image1;
	}
	catch (const char* err)
	{
		cout << err << endl;
	}

	return 0;
}