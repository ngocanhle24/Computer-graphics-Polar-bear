#pragma once

class Pixel
{
private:
	unsigned int red;
	unsigned int green;
	unsigned int blue;

public:
	Pixel();
	Pixel(const Pixel&); //? copy constructor
	Pixel(unsigned int, unsigned int, unsigned int);
	~Pixel();

	const unsigned int &operator[](const char *) const; //? getter offset
	unsigned int &operator[](const char *);				//? setter offset

	class InputOutOfBoundsExeption
	{
	private:
		const char *errorMessage;
		const char *offendingIndex;

	public:
		InputOutOfBoundsExeption(const char *, const char *);

		const char *returnError();
		const char *returnOffendingIndex();
	};
};