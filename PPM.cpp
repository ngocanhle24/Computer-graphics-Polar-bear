#include "PPM.h"

#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

PPM::PPM()
	: magic(""), comment(""), height(0), width(0), maxColor(0), pixels({})
{
	cout << "Default PPM constructor called." << endl;
}

PPM::PPM(const PPM& img)
	: magic(img.magic), comment(img.comment), height(img.height), width(img.width), maxColor(img.maxColor), pixels(img.pixels)
{
	cout << "PPM copy constructor called." << endl;

	// copy pixels to vector
	for (int i = 0; i < img.pixels.size(); i++)
		pixels.emplace_back(Pixel(img.pixels[i])); // emplace pixel
}

PPM::PPM(PPM&& img)
	: magic(img.magic), comment(img.comment), height(img.height), width(img.width), maxColor(img.maxColor), pixels(move(img.pixels))
{
	cout << "PPM move constructor called." << endl;
}

PPM::PPM(ifstream& infile)
{
	cout << "1-arg PPM constructor called." << endl;

	// get magix number and comment
	getline(infile, magic);
	getline(infile, comment);

	// get width, height, color depth
	infile >> width >> height >> maxColor;

	// emplace pixels to vector
	unsigned int r, g, b, numPixels = width * height;
	for (int i = 0; i < numPixels; i++)
	{
		infile >> r >> g >> b; // get rgb values
		pixels.emplace_back(Pixel(r, g, b)); // emplace anon pixel
	}
}

PPM::~PPM()
{
	cout << "PPM destructor called." << endl;
}

string PPM::getComment()
{
	return comment;
}

string PPM::getMagic()
{
	return magic;
}

unsigned int PPM::getMaxColor()
{
	return maxColor;
}

unsigned int PPM::getHeight()
{
	return height;
}

unsigned int PPM::getWidth()
{
	return width;
}

unsigned int PPM::getSize()
{
	return height * width;
}

void PPM::setComment(string str)
{
	comment = str;
}

void PPM::setMagic(string str)
{
	magic = str;
}

void PPM::setMaxColor(unsigned int num)
{
	maxColor = num;
}

void PPM::setHeight(unsigned int num)
{
	height = num;
}

void PPM::setWidth(unsigned int num)
{
	width = num;
}

const Pixel& PPM::operator[](unsigned int num) const
{
	return pixels[num];
}

Pixel& PPM::operator[](unsigned int num)
{
	return pixels[num];
}

const PPM& PPM::operator=(const PPM& img)
{
	cout << "PPM copy assignment called." << endl;

	// check for self-assignment
	if (this == &img)
		return *this;

	// copy data members
	magic = img.magic;
	comment = img.comment;
	height = img.height;
	width = img.width;
	maxColor = img.maxColor;

	// copy pixels to vector
	pixels.clear(); // clear vector
	for (int i = 0; i < img.pixels.size(); i++)
		pixels.emplace_back(Pixel(img.pixels[i])); // emplace pixel

	return *this;
}

const PPM& PPM::operator=(PPM&& img)
{
	cout << "PPM move assignment called." << endl;

	// check for self-assignment
	if (this == &img)
		return *this;

	// copy data members
	magic = img.magic;
	comment = img.comment;
	height = img.height;
	width = img.width;
	maxColor = img.maxColor;

	// move vector
	pixels = move(img.pixels);

	return *this;
}
