#define _USE_MATH_DEFINES
#include "Graphics.h"
#include <algorithm>
#include "graphics.h"
#include <iostream>
#include <vector>
#include <cmath>

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
		v = 0.0625;
		kernel = {
			v, 2*v, v,
			2*v, 4*v, 2*v,
			v, 2*v, v};
	}
	else if (!strcmp(filterType, "sharpen"))
	{
		v = double(1)/double(3);
		kernel = {
			0, -v, 0,
			-v, 5*v, -v,
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
	else if (!strcmp(filterType, "magic"))
	{
		kernel = {
			0, 0, 1,
			0, 1, 0,
			0, 0, 1};
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
				double total = 0;
				int loc = (i * c + j);
				for (unsigned int m = 0; m < 9; m++)
				{
					unsigned int index = loc + offset[m];

					// This if-statement aims to ignore out-of-bound neighbor pixels,
					// however some surround pixels are still included in "total" because pixels are stored in 1D array
					// The distortion is small (pixel is very small), so it doesn't affect much
					if (index >= 0 && index < image.getSize())
					{
						total += kernel[m] * double(newImage[index][rgb[k]]);
					}
				}
				image[loc][rgb[k]] = (unsigned int)total;
			}
		}
	}
	cout << filterType << " succeeds\n";
	return image;
}

const PPM& Graphics::makeGrayscale(PPM& image) {
	for (int i = 0; i < image.getSize(); i++) {
		unsigned int num = (image[i]["red"] + image[i]["green"] + image[i]["blue"]) / 3.0;
		image[i] = Pixel(num, num, num);
	}

	return image;
}

const PPM& Graphics::rotateImage(PPM& image, double angle) {
	int c = image.getWidth();
	int r = image.getHeight();

	PPM blackCanvas;
	blackCanvas.setHeight(r);
	blackCanvas.setWidth(c);
	blackCanvas.setComment("Image rotated " + to_string(angle) + " degrees\n");
	blackCanvas.setMagic(image.getMagic());
	blackCanvas.setMaxColor(image.getMaxColor());
	blackCanvas.resize(c * r);

	double radians = -angle * M_PI / 180.0;

	//Image center
	double centerX = double(c) / 2.0;
	double centerY = double(r) / 2.0;
	
	for (unsigned int i = 0; i < r; i++) {
		for (unsigned int j = 0; j < c; j++) {
			//Convert (x,y) pixel coordinate relative to center coordinate (0,0)
			double oldX = j - centerX;
			double oldY = centerY - i;

			// Apply rotation transformation
			/* Rotation matrix
				[cos(alpha)		-sin(alpha)]
				[sin(alpha)		cos(alpha)]
			*/
			double rotatedX = oldX * cos(radians) - oldY * sin(radians);
			double rotatedY = oldX * sin(radians) + oldY * cos(radians);

			//Convert back to coordinate on pixels
			double newX = rotatedX + centerX;
			double newY = centerY - rotatedY;

			if (newX >= 0 && newY >= 0 && newX < c && newY < r) {
				int oldLoc = i * c + j;
				int newLoc = int(newY) * c + int(newX); //Round down pixel index

				//then also paste it to pixels around it
				blackCanvas[newLoc] = image[oldLoc];
				if(newX + 1 < c) blackCanvas[newLoc+1] = image[oldLoc];
				if (newY + 1 < r) {
					blackCanvas[newLoc + c] = image[oldLoc];
					if (newX + 1 < c) blackCanvas[newLoc + c + 1] = image[oldLoc];
				}
			}
		}
	}

	image = blackCanvas;
	return blackCanvas;
}

//const PPM& Graphics::scaleImage(PPM& image, double factor) {}

const PPM& Graphics::translateImage(PPM& image, int dx, int dy) {
	int c = image.getWidth();
	int r = image.getHeight();

	//Create a black canvas
	PPM blackCanvas;
	blackCanvas.setHeight(r);
	blackCanvas.setWidth(c);
	blackCanvas.setComment("Image translates " + to_string(dx) + " pixels horizontally, " + to_string(dy) + " px vertically");
	blackCanvas.setMagic(image.getMagic());
	blackCanvas.setMaxColor(image.getMaxColor());
	blackCanvas.resize(c * r);

	//Fill the remaining area of original image on the black canvas after translating
	//But this tranlastion does not support for several seperate translations because some pixels will be lost due to out of viewport
	for (unsigned int i = 0; i < r; i++) {
		for (unsigned int j = 0; j < c; j++) {
			unsigned int old_loc = i * c + j;
			unsigned int x = j + dx, y = i - dy;

			if (x < c && y < r && x >= 0 && y >= 0) {
				unsigned int new_loc = y * c + x;
				blackCanvas[new_loc] = image[old_loc];
			}
		}
	}
	image = blackCanvas;

	return image;
}