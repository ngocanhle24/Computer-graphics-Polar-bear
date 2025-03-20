#include "Graphics.h"

#include <iostream>
#include <vector>

Graphics::Graphics() {};
const PPM &Graphics::applyFilter(PPM &image, const char *filterType)
{
	vector<double> kernel(9);
	int c = image.getWidth();
	int r = image.getHeight();
	/* c = columns = width, r = rows = height
		[i-c-1]          [i-c]          [i-c+1]               [][][]
		[i-1]            [i]            [i+1]                 [][][]
		[i+c-1]          [i+c]          [i+c+1]               [][][]
	*/
	vector<int> offset = {
		-c-1, -c, -c+1,
		-1, 0, 1,
		 c-1, c, c+1};

	double v;
	if (!strcmp(filterType, "blur"))
	{
		v = 1 / 9;
		kernel = {
			v, v, v,
			v, v, v,
			v, v, v};
	}
	else if (!strcmp(filterType, "sharpen"))
	{
		v = 1 / 3;
		kernel = {
			0, -v, 0,
			-v, 7 * v, -v,
			0, -v, 0};
	}
	else if (!strcmp(filterType, "edgeDetect"))
	{
		kernel = {
			0, 1, 0,
			1, -4, 1,
			0, 1, 0};
	}
	else if (!strcmp(filterType, "emboss"))
	{
		kernel = {
			-2, -1, 0,
			-1, 1, 1,
			0, 1, 2};
	}
	else if (!strcmp(filterType, "laplacian"))
	{
		kernel = {
			0, -1, 0,
			-1, 4, -1,
			0, -1, 0};
	}

	vector<const char *> rgb = {"red", "green", "blue"};
	PPM newImage(image); // what should be returned the original image or newImage
	// need a temporary same image to work on computation
	// can't compute on the origin image matrix, which needs modification

	for (unsigned int i = 0; i < r; i++)
	{
		for (unsigned int j = 0; j < c; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				int total = 0;
				int loc = (i * c + j);
				for (unsigned int m = 0; m < 9; m++)
				{
					unsigned int index = loc + offset[m];

					// This if-statement aims to ignore out-of-bound neighbor pixels,
					// however some surround pixels are still included in "total" because pixels are stored in 1D array
					// The distortion is small (pixel is very small), so it doesn't affect much
					if (index >= 0 && index < image.getSize())
					{
						total += kernel[m] * newImage[index][rgb[k]];
					}
				}
				image[loc][rgb[k]] = total;
			}
		}
	}
	cout << filterType << " succeeds\n";
	return image;
}

// const PPM& Graphics::makeGrayScale(PPM& image) {
//
// }
// const PPM& Graphics::rotateImage(PPM& image, double angle) {
//
// }

const PPM& Graphics::scaleImage(PPM& image, double factor) {
	image.resize(factor);
	cout << "resize completed" << endl;
	return image;
}

// const PPM& Graphics::translateImage(PPM& image, int dx, int dy) {
//
// }