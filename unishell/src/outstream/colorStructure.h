#pragma once

enum Color {
	null = 0,

	red = 31, green, yellow, blue,
	purple, cyan, white,

	// bright colors
	gray = 90, wred, wgreen, wyellow,
	wblue, wpurple, wcyan
};

enum ColorMode {
	normal = 0,
	dark = 2,
	italic = 3,
	underline = 4,
	crossed = 9
};

class ColorStructure
{
public:
	ColorStructure(unsigned int id, ColorMode mode = normal) : id(id), mode(mode) {}



	unsigned int id;
	ColorMode mode;
};