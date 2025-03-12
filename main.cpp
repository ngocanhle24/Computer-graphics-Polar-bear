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
	ifstream infile("Shahriar.ppm");
	PPM *image1 = new PPM(infile);
	// PPM* image2 = new PPM(*image1);
	// PPM* image3 = new PPM(*image1);
	// PPM* image4 = new PPM(*image1);

	// print(bearImage);
	Graphics g;
	// g.applyFilter(*image1, "edgeDetect");
	g.applyFilter(*image1, "laplacian");
	/*g.applyFilter(*image1, "blur");
	g.applyFilter(*image1, "blur");
	g.applyFilter(*image1, "blur");
	g.applyFilter(*image1, "blur");*/
	image1->saveImageToFile("filtered_polar_bear.ppm");

	delete image1;

	return 0;
}