#pragma once

#include "PPM.h"

class Graphics
{
public:
	Graphics();
	const PPM& applyFilter(PPM &, const char *);
	const PPM& makeGrayscale(PPM &);
	const PPM& rotateImage(PPM &, double);
	const PPM& scaleImage(PPM &, double);
	const PPM& translateImage(PPM &, int, int);
};