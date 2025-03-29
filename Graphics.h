#pragma once

#include "PPM.h"

class Graphics
{
public:
	Graphics();

	static void applyFilter(PPM&, const char *);
	static void makeGrayscale(PPM&);
	static void rotateImage(PPM&, double);
	static void scaleImage(PPM&, double);
	static void translateImage(PPM&, int, int);
	static void invertColors(PPM&);
};