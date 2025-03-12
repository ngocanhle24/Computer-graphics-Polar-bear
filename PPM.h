#pragma once

#include <string>
#include <vector>

#include "Pixel.h"

using namespace std;

class PPM
{
private:
	string magic, comment;
	unsigned int height, width, maxColor;
	vector<Pixel> pixels;

public:
	PPM();
	PPM(const PPM &); //? copy constructor
	PPM(PPM &&);	  //? move constructor
	PPM(ifstream &);
	~PPM();

	//? data member getters
	string getComment() const;
	string getMagic() const;
	unsigned int getMaxColor() const;
	unsigned int getHeight() const;
	unsigned int getWidth() const;
	unsigned int getSize() const;

	//? data member setters
	void setComment(string);
	void setMagic(string);
	void setMaxColor(unsigned int);
	void setHeight(unsigned int);
	void setWidth(unsigned int);

	const Pixel &operator[](unsigned int) const; //? getter offset
	Pixel &operator[](unsigned int);			 //? setter offset
	const PPM &operator=(const PPM &);			 //? copy assignment
	const PPM &operator=(PPM &&);				 //? move assignment

	void resize(unsigned int);
	void saveImageToFile(string) const;
};