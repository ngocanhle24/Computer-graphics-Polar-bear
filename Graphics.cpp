#define _USE_MATH_DEFINES

#include "Graphics.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>

using namespace std;

const PPM& Graphics::applyFilter(PPM &image, const char *filterType)
{
	clock_t start = clock();

	int c = image.getWidth(), r = image.getHeight();
	double v;
	vector<double> kernel(9);
	vector<int> offset = {-c-1,-c,-c+1, -1,0,1, c-1,c,c+1};

	if (!strcmp(filterType, "blur"))
	{
		v = 0.0625;
		kernel = {v,2*v,v, 2*v,4*v,2*v, v,2*v,v};
	}
	else if (!strcmp(filterType, "sharpen"))
	{
		v = double(1)/double(3);
		kernel = {0,-v,0, -v,5*v,-v, 0,-v,0};
	}
	else if (!strcmp(filterType, "edgeDetect"))
		kernel = {1,0,-1, 0,0,0, 1,0,-1};
	else if (!strcmp(filterType, "emboss"))
		kernel = {-2,-1,0, -1,1,1, 0,1,2};
	else if (!strcmp(filterType, "magic"))
		kernel = {0,0,1, 0,1,0, 0,0,1};

	vector<const char *> rgb = {"red", "green", "blue"};
	PPM tempImage(image);

	for (unsigned int i = 0; i < r; i++)
		for (unsigned int j = 0; j < c; j++)
			for (int k = 0; k < 3; k++)
			{
				double total = 0;
				int loc = (i * c + j);
				for (unsigned int m = 0; m < 9; m++)
				{
					unsigned int index = loc + offset[m];

					if (index >= 0 && index < image.getSize()) //1-pixel border around the edge of the image won't be filtered properly due to 1D array pixel, but too small to see
						total += kernel[m] * double(tempImage[index][rgb[k]]);

				}
				image[loc][rgb[k]] = (unsigned int)total;
			}

	clock_t end = clock();
	std::cout << "Filter \"" << filterType << "\" completed in " << end - start << "ms." << endl;

	return image;
}

const PPM& Graphics::makeGrayscale(PPM& image) {
	clock_t start = clock();

	for (int i = 0; i < image.getSize(); i++) {
		unsigned int num = (image[i]["red"] + image[i]["green"] + image[i]["blue"]) / 3.0;
		image[i] = Pixel(num, num, num);
	}

	clock_t end = clock();
	std::cout << "Grayscale completed in " << end - start << "ms." << endl;

	return image;
}

const PPM& Graphics::rotateImage(PPM& image, double angle) {
	clock_t start = clock();

	int c = image.getWidth();
	int r = image.getHeight();

	PPM blackCanvas;
	blackCanvas.setHeight(r);
	blackCanvas.setWidth(c);
	blackCanvas.setComment("Image rotated " + to_string(angle) + " degrees");
	blackCanvas.setMagic(image.getMagic());
	blackCanvas.setMaxColor(image.getMaxColor());
	blackCanvas.resize(c * r);

	double radians = -angle * M_PI / 180.0;

	//Image center
	double centerX = double(c) / 2.0;
	double centerY = double(r) / 2.0;
	
	for (unsigned int i = 0; i < r; i++) {
		for (unsigned int j = 0; j < c; j++) {
			//Convert (i,j) pixel relative to center (0,0)
			double X = j - centerX;
			double Y = centerY - i;

			// Apply rotation transformation
			/* Rotation matrix
				[cos(alpha)		-sin(alpha)]
				[sin(alpha)		cos(alpha)]
			*/
			double rotatedX = X * cos(radians) - Y * sin(radians);
			double rotatedY = X * sin(radians) + Y * cos(radians);

			//Convert back to coordinate on pixels
			double new_j = rotatedX + centerX;
			double new_i = centerY - rotatedY;

			if (new_i >= 0 && new_j >= 0 && new_i < r && new_j < c) {
				int oldLoc = i * c + j;
				int newLoc = int(new_i) * c + int(new_j); //Round down pixel index

				blackCanvas[newLoc] = image[oldLoc];
				//also paste it to pixels around it to avoid black holes
				//[current  ][newLoc+1  ]
				//[newLoc + c][newLoc+c+1]

				if(new_j + 1 < c) blackCanvas[newLoc+1] = image[oldLoc];
				if (new_i + 1 < r) {
					blackCanvas[newLoc + c] = image[oldLoc];
					if (new_j + 1 < c) blackCanvas[newLoc + c + 1] = image[oldLoc];
				} //NEAREST NEIGHBOR INTERPOLATION
			}
		}
	}
	image = blackCanvas;

	clock_t end = clock();
	std::cout << "Rotation completed in " << end - start << "ms." << endl;

	return image;
}

// Scale image with positive and negative scaling factors
const PPM& Graphics::scaleImage(PPM& image, double factor) {
	clock_t start = clock();

	if (factor == 0)
		image = PPM();

	int c = image.getWidth();
	int r = image.getHeight();

	PPM scaledImg;
	scaledImg.setHeight(round(double(r) * abs(factor)));
	scaledImg.setWidth(round(double(c) * abs(factor)));
	scaledImg.setComment("Image scaled by " + to_string(factor) + " time(s) in both direction");
	scaledImg.setMagic(image.getMagic());
	scaledImg.setMaxColor(image.getMaxColor());

	int scaledHeight = scaledImg.getHeight();
	int scaledWidth = scaledImg.getWidth();
	scaledImg.resize(scaledHeight * scaledWidth);

	for (unsigned int i = 0; i < scaledHeight; i++) {
		for (unsigned int j = 0; j < scaledWidth; j++) {
			//Map pixels on scaledImg to original image
			int x = int(double(j) / abs(factor));
			int y = int(double(i) / abs(factor));
			if (factor < 0) x = c - 1 - x;

			unsigned int originLoc = y * c + x;			
			unsigned int scaledLoc = i * scaledWidth + j;
			scaledImg[scaledLoc] = image[originLoc]; //NEAREST NEIGHBOR INTERPOLATION
		}
	}
	image = scaledImg;

	clock_t end = clock();
	std::cout << "Scaling completed in " << end - start << "ms." << endl;

	return image;
}

const PPM& Graphics::translateImage(PPM& image, int dx, int dy) {
	clock_t start = clock();

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

	clock_t end = clock();
	std::cout << "Translation completed in " << end - start << "ms." << endl;

	return image;
}

const PPM& Graphics::invertColors(PPM& image)
{
	clock_t start = clock();
	unsigned int maxColor = image.getMaxColor();

	for (int i = 0; i < image.getSize(); i++) // loop thru pixels
	{
			image[i]["red"] = maxColor - image[i]["red"];
			image[i]["green"] = maxColor - image[i]["green"];
			image[i]["blue"] = maxColor - image[i]["blue"];
	}

	clock_t end =clock();
	std::cout << "Inversion completed in " << end - start << "ms." << endl;

	return image;
}
