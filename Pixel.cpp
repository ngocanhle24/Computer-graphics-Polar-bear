#include "Pixel.h"

#include <iostream>

using namespace std;

Pixel::InputOutOfBoundsExeption::InputOutOfBoundsExeption(const char* err, const char* idx)
	: errorMessage(err), offendingIndex(idx)
{

}

const char* Pixel::InputOutOfBoundsExeption::returnError()
{
	return errorMessage;
}

const char* Pixel::InputOutOfBoundsExeption::returnOffendingIndex()
{
	return offendingIndex;
}

Pixel::Pixel()
	: red(0), green(0), blue(0)
{
	cout << "Default Pixel constructor called." << endl;
}

Pixel::Pixel(const Pixel& pxl)
	: red(pxl.red), green(pxl.green), blue(pxl.blue)
{
	cout << "Pixel copy constructor called." << endl;
}

Pixel::Pixel(unsigned int r, unsigned int g, unsigned int b)
	: red(r), green(g), blue(b)
{
	cout << "3-arg Pixel constructor called." << endl;
}

Pixel::~Pixel()
{
	cout << "Pixel destructor called." << endl;
}

const unsigned int& Pixel::operator[](const char* cstr)
{
	try
	{
		if (cstr == "red")
			return red;
		else if (cstr == "green")
			return green;
		else if (cstr == "blue")
			return blue;
		else
			throw InputOutOfBoundsExeption("Error! Invalid index.", cstr); //! throw point
	}
	catch (InputOutOfBoundsExeption ex)
	{
		throw ex; //! re-throw
	}
}
