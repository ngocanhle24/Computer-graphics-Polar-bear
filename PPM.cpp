#include "PPM.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

PPM::PPM()
	: magic(""), comment(""), height(0), width(0), maxColor(0), pixels({})
{
	// cout << "Default PPM constructor called." << endl;
}

PPM::PPM(const PPM &img)
	: magic(img.magic), comment(img.comment), height(img.height), width(img.width), maxColor(img.maxColor), pixels(img.pixels)
{ // vector is already initialized in member initializer list, no need for a for loop?
  // cout << "PPM copy constructor called." << endl;
}

PPM::PPM(PPM &&img)
	: magic(img.magic), comment(img.comment), height(img.height), width(img.width), maxColor(img.maxColor), pixels(move(img.pixels))
{
	// cout << "PPM move constructor called." << endl;
}

PPM::PPM(ifstream &infile)
{
	// cout << "1-arg PPM constructor called." << endl;

	// get magix number and comment
	getline(infile, magic);
	while (infile.peek() == '#')
	{ // read comment on several lines
		string line;
		getline(infile, line);
		comment += line;
	}

	// get width, height, color depth
	infile >> width >> height >> maxColor;

	// emplace pixels to vector
	unsigned int r, g, b;
	while (infile >> r >> g >> b)
	{
		pixels.emplace_back(r, g, b); // emplace Pixel(r,b,g)
	}
}

PPM::~PPM()
{
	// cout << "PPM destructor called." << endl;
}

string PPM::getComment() const
{
	return comment;
}

string PPM::getMagic() const
{
	return magic;
}

unsigned int PPM::getMaxColor() const
{
	return maxColor;
}

unsigned int PPM::getHeight() const
{
	return height;
}

unsigned int PPM::getWidth() const
{
	return width;
}

unsigned int PPM::getSize() const
{
	return height * width;
}

void PPM::setComment(string str)
{
	comment = '#' + str;
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

const Pixel &PPM::operator[](unsigned int num) const
{
	if (num < 0 || num >= getSize())
		throw runtime_error("Pixel index out of bounds\n");
	return pixels[num];
}

Pixel &PPM::operator[](unsigned int num)
{
	if (num < 0 || num >= getSize())
		throw runtime_error("Pixel index out of bounds\n");
	return pixels[num];
}

const PPM &PPM::operator=(const PPM &img)
{
	// cout << "PPM copy assignment called." << endl;

	// check for self-assignment
	if (this != &img)
	{
		// copy data members
		magic = img.magic;
		comment = img.comment;
		height = img.height;
		width = img.width;
		maxColor = img.maxColor;

		// copy pixels to vector
		pixels = img.pixels; // vector "=" operator automatically reallocate for new size and assign all elements
	}
	return *this;
}

const PPM &PPM::operator=(PPM &&img)
{
	// cout << "PPM move assignment called." << endl;

	// check for self-assignment
	if (this != &img)
	{
		// copy data members
		magic = img.magic;
		comment = img.comment;
		height = img.height;
		width = img.width;
		maxColor = img.maxColor;

		// copy pixels to vector
		pixels = move(img.pixels);
	}
	return *this;
}
void PPM::saveImageToFile(string file) const
{
	ofstream outFile(file);
	try
	{
		if (!outFile.fail())
		{
			outFile << magic << "\n"
					<< comment << "\n"
					<< width << " " << height << "\n"
					<< maxColor << "\n";
			for (auto pixel : pixels)
			{
				outFile << pixel["red"] << " " << pixel["green"] << " " << pixel["blue"] << " ";
			}
			outFile.close();
		}
		else
			throw "File can't be opened\n";
	}
	catch (const char *s)
	{
		cout << s;
		throw;
	}
}

void PPM::resize(unsigned int n)
{
	/* store width & height */
	int w = getWidth();
	int h = getHeight();

	/* update width & height */
	setWidth(ceil(w/n));
	setHeight(ceil(h/n));

	/* write every nth pixel to a new vector of pixels */
	vector<Pixel> temp;
	for (int row = 0; row < h; row++) // loop thru rows
		for (int col= 0; col < w; col++) // loop thru columns
			if (row % n != 0 && col % n != 0)
				temp.emplace_back(pixels[row*w+col]); // write pixel to temp

	pixels.clear(); // clear pixels
	pixels = temp; // repopulate pixels
}