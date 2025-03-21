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

	/* store width & height */
	int w = image.getWidth();
	int h = image.getHeight();

	vector<Pixel> temp; // temp vector for use in scale up/down operation

	/* reverse image if factor if negative */
	//if (factor < 0)
	//{
	//	int lastIdx = image.getSize() - 1;
	//	for (int i = 0; i < floor(image.getSize()/2); i++)
	//		swap(image[i], image[lastIdx - i]);
	//}

	if (abs(factor) < 1) // scale down
	{
		/* emplace every nth (1/factor) pixel to temp */
		int n = abs(ceil(1 / factor));
		for (int row = 0; row < h; row++) // loop thru rows
			for (int col = 0; col < w; col++) // loop thru columns
				if (row % n == 0 && col % n == 0)
					temp.emplace_back(image[row * w + col]); // write pixel to temp
	}
	else if (abs(factor) > 1) // scale up
	{
		//- TODO: implement scale up logic
	}

	/* copy pixels from temp */
	image.resize(temp.size()); // resize image.pixels to fit temp
	image.setWidth(ceil(w * factor)); // update width
	image.setHeight(ceil(h * factor)); // update height
	for (int i = 0; i < temp.size(); i++)
		image[i] = temp[i]; // copy temp pixel to image.pixels
	return image;
}

// const PPM& Graphics::translateImage(PPM& image, int dx, int dy) {
//
// }