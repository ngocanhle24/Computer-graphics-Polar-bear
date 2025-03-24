#include "Graphics.h"

#include <iostream>
#include <vector>

Graphics::Graphics() {};
const PPM &Graphics::applyFilter(PPM &image, const char *filterType)
{
	vector<double> kernel(9);
	int w = image.getWidth(), h = image.getHeight();

	vector<int> offset = { -w-1,-w,-w+1, -1,0,1, w-1,w,w+1 };

	if (!strcmp(filterType, "blur"))
	{
		double v = 1 / 9;
		kernel = { v,v,v, v,v,v, v,v,v };
	}
	else if (!strcmp(filterType, "sharpen"))
	{
		double v = 1 / 3;
		kernel = { 0,-v,0, -v,7 * v,-v, 0,-v,0 };
	}
	else if (!strcmp(filterType, "edgeDetect"))
		kernel = { 0,1,0, 1,-4,1, 0,1,0 };
	else if (!strcmp(filterType, "emboss"))
		kernel = { -2,-1,0, -1,1,1, 0,1,2 };
	else if (!strcmp(filterType, "laplacian"))
		kernel = { 0,-1,0, -1,4,-1, 0,-1,0 };

	vector<const char *> rgb = {"red", "green", "blue"};
	PPM newImage(image);

	for (unsigned int i = 0; i < h; i++) // loop thru rows (row-major navigation)
		for (unsigned int j = 0; j < w; j++) // loop thru columns
		{
			int loc = (i * w + j);
			for (unsigned int k = 0; k < 3; k++) // loop thru RGB
			{
				unsigned int total = 0;
				for (unsigned int m = 0; m < 9; m++) // loop thru kernel
				{
					unsigned int index = loc + offset[m];
					if (index >= 0 && index < image.getSize()) // if current position + offset isn't out of bounds
						total += kernel[m] * newImage[index][rgb[k]];
				}
				image[loc][rgb[k]] = total;
			}
		}

	cout << filterType << " filter applied." << endl;
	return image;
}

// const PPM& Graphics::makeGrayScale(PPM& image) {
//
// }
// const PPM& Graphics::rotateImage(PPM& image, double angle) {
//
// }

void emplacePixelNTimes(Pixel pixel, vector<Pixel>& vec, int n)
{
	for (int count = n; count > 0; count--) // loop n times
		vec.emplace_back(pixel);

}

void emplaceRowNTimes(PPM& image, vector<Pixel>& vec, unsigned int row, int n)
{
	unsigned int w = image.getWidth(), numCols = w;
	for (int count = n; count > 0; count--) // loop n times
		for (int col = 0; col < numCols; col++) // loop thru columns
			emplacePixelNTimes(image[col + row * w], vec, n);
}

void reversePixels(PPM& image)
{
	unsigned int last = image.getSize() - 1;
	for (int i = 0; i < image.getSize(); i++)
	{
		Pixel temp(image[i]);
		image[i] = image[last - i];
		image[last - i] = temp;
	}
}

const PPM& Graphics::scaleImage(PPM& image, double factor) {

	/* store width & height */
	int w = image.getWidth();
	int h = image.getHeight();

	vector<Pixel> temp; // temp vector for use in scale up/down operation

	/* reverse image if factor is negative */
	if (factor < 0)
	{
		reversePixels(image); // reverse pixel array
		factor = abs(factor); // ensure that factor isn't negative
	}

	/* scale image if factor != 1 */
	if (factor < 1) // scale down
	{
		/* emplace every nth (1/factor) pixel to temp */
		int n = ceil(1 / factor);
		for (int row = 0; row < h; row++) // loop thru rows
			for (int col = 0; col < w; col++) // loop thru columns
				if (row % n == 0 && col % n == 0)
					temp.emplace_back(image[row * w + col]); // emplace pixel if row & col are divisible by n
	}
	else if (factor > 1) // scale up
	{
		//- TODO: implement scale up logic
		unsigned int numRows = image.getHeight();
		for (int row = 0; row < numRows; row++) // loop thru rows
			emplaceRowNTimes(image, temp, row, factor);
	}

	/* copy pixels from temp if factor != 1 */
	if (factor != 1)
	{
		image.resize(temp.size()); // resize image.pixels to fit temp
		image.setWidth(ceil(w * factor)); // update width
		image.setHeight(ceil(h * factor)); // update height
		for (int i = 0; i < temp.size(); i++)
			image[i] = temp[i]; // copy temp pixel to image.pixels
	}

	cout << "Scale image applied." << endl;
	return image;
}

// const PPM& Graphics::translateImage(PPM& image, int dx, int dy) {
//
// }