#pragma once

#include <string>


#define tostr std::to_string
#define endclr "\033[0m"

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


Color stringToColor(const std::string& strMode);
std::string colorEnumToString(const Color color);

ColorMode stringToColorMode(const std::string& strMode);
std::string colorModeEnumToString(const ColorMode mode);


// returns the color assigned to the id (0 - 255)
inline std::string id(const unsigned int i, const ColorMode mode) noexcept {
	return "\033[" + tostr((int)mode) + ";38;5;" + tostr(i) + 'm';
}

// returns rgb ANSI notation
inline std::string rgb(const unsigned int red, const unsigned int green, const unsigned int blue, const ColorMode mode) noexcept {
	return "\033[" + tostr((int)mode) + ";38;2;" + tostr(red) + ';' + tostr(green) + ';' + tostr(blue) + 'm';
}

inline std::string colorToString(const Color color, const ColorMode mode) noexcept {
	return "\033[" + tostr((int)mode) + ';' + tostr((int)color) + 'm';
}

class BaseColorStructure
{
public:
	virtual std::string toString() const = 0;
	virtual std::string toStrColorStructure() const = 0;
};

class IdColorStructure : public BaseColorStructure
{
public:
	explicit IdColorStructure(const unsigned int idc, const ColorMode mode = normal) : mode(mode), idc(idc) {}

	std::string toString() const override {
		return id(idc, mode);
	}

	std::string toStrColorStructure() const override {
		return "id:" + tostr(idc) + ',' + colorModeEnumToString(mode) + ':';
	}


	unsigned int idc;
	ColorMode mode;

	static constexpr size_t argSize = 1;
};

class RGBColorStructure : public BaseColorStructure
{
public:
	RGBColorStructure(const unsigned int red, const unsigned int green, const unsigned int blue, const ColorMode mode = normal) :
		mode(mode), red(red), green(green), blue(blue) {}

	std::string toString() const noexcept override {
		return rgb(red, green, blue, mode);
	}

	std::string toStrColorStructure() const override {
		return "rgb:" + tostr(red) + ',' + tostr(green) + ',' + tostr(blue) + ',' + colorModeEnumToString(mode) + ':';
	}


	unsigned int red;
	unsigned int green;
	unsigned int blue;

	ColorMode mode;

	static constexpr size_t argSize = 3;
};

class ColorStructure : public BaseColorStructure
{
public:
	explicit ColorStructure(const Color color, const ColorMode mode = normal) :
		mode(mode), color(color) {}

	std::string toString() const override {
		return colorToString(color, mode);
	}

	std::string toStrColorStructure() const override {
		return "clr:" + colorEnumToString(color) + ',' + colorModeEnumToString(mode) + ':';
	}


	Color color;
	ColorMode mode;

	static constexpr size_t argSize = 1;
};
