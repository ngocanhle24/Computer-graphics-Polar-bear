#include "Pixel.h"
#include <cstring>

#include <iostream>

using namespace std;

Pixel::InputOutOfBoundsExeption::InputOutOfBoundsExeption(const char *err, const char *idx)
	: errorMessage(err), offendingIndex(idx)
{
}

const char *Pixel::InputOutOfBoundsExeption::returnError()
{
	return errorMessage;
}

const char *Pixel::InputOutOfBoundsExeption::returnOffendingIndex()
{
	return offendingIndex;
}

Pixel::Pixel()
	: red(0), green(0), blue(0)
{
	// cout << "Default Pixel constructor called." << endl;
}

Pixel::Pixel(const Pixel &pxl)
	: red(pxl.red), green(pxl.green), blue(pxl.blue)
{
	// cout << "Pixel copy constructor called." << endl;
}

Pixel::Pixel(unsigned int r, unsigned int g, unsigned int b)
	: red(r), green(g), blue(b)
{
	// cout << "3-arg Pixel constructor called." << endl;
}

Pixel::~Pixel()
{
	// cout << "Pixel destructor called." << endl;
}

const unsigned int &Pixel::operator[](const char *cstr) const
{
	try
	{
		if (!strcmp(cstr, "red"))
			return red; // use cstring method for char* comparison
		if (!strcmp(cstr, "green"))
			return green;
		if (!strcmp(cstr, "blue"))
			return blue;

		throw InputOutOfBoundsExeption("Error! Invalid index.", cstr); //! throw point
	}
	catch (Pixel::InputOutOfBoundsExeption &ex)
	{
		cout << ex.returnError() << ex.returnOffendingIndex() << " is an invalid color index\n";
		throw; // re-throw
	}
}

// Setter offset
unsigned int &Pixel::operator[](const char *cstr)
{
	try
	{
		if (!strcmp(cstr, "red"))
			return red;
		if (!strcmp(cstr, "green"))
			return green;
		if (!strcmp(cstr, "blue"))
			return blue;

		throw InputOutOfBoundsExeption("Error! Invalid index.", cstr); //! throw point
	}
	catch (Pixel::InputOutOfBoundsExeption &ex)
	{
		cout << ex.returnError() << ex.returnOffendingIndex() << " is an invalid color index\n";
		throw; // re-throw
	}
}