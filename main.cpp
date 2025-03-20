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

		Graphics g;

		g.applyFilter(*image1, "blur"); // filter image
		image1->saveImageToFile(filename + "_blur.ppm");
		g.applyFilter(*image2, "sharpen"); // filter image
		image2->saveImageToFile(filename + "_sharpen.ppm");
		g.applyFilter(*image3, "edgeDetect"); // filter image
		image3->saveImageToFile(filename + "_edgeDetect.ppm");
		g.applyFilter(*image4, "emboss"); // filter image
		image4->saveImageToFile(filename + "_emboss.ppm");
		g.applyFilter(*image5, "lapacian"); // filter image
		image5->saveImageToFile(filename + "_lapacian.ppm");

		g.scaleImage(*image6, 2); // resize image by factor
		image6->saveImageToFile(filename + "_resize.ppm");

		delete image1;
	}
	catch (const char* err)
	{
		cout << err << endl;
	}

	return 0;
}