#pragma once

#include "PPM.h"

class Graphics
{
public:
	static const PPM& applyFilter(PPM&, const char *);
	static const PPM& makeGrayscale(PPM&);
	static const PPM& rotateImage(PPM&, double);
	static const PPM& scaleImage(PPM&, double);
	static const PPM& translateImage(PPM&, int, int);
	static const PPM& invertColors(PPM&);
};
