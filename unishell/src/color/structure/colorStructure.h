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

ColorMode stringToColorMode(const std::string& strMode);



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
	virtual ~BaseColorStructure() = default;
	explicit BaseColorStructure(const ColorMode mode = normal) : mode(mode) {}

	virtual std::string toString() const = 0;

	ColorMode mode;
};

class IdColorStructure : public BaseColorStructure
{
public:
	explicit IdColorStructure(const unsigned int idc, const ColorMode mode = normal) : BaseColorStructure(mode), idc(idc) {}

	std::string toString() const override {
		return id(idc, mode);
	}

	unsigned int idc;

	static constexpr size_t argSize = 1;
};

class RGBColorStructure : public BaseColorStructure
{
public:
	RGBColorStructure(const unsigned int red, const unsigned int green, const unsigned int blue, const ColorMode mode = normal) :
		BaseColorStructure(mode), red(red), green(green), blue(blue) {}

	std::string toString() const noexcept override {
		return rgb(red, green, blue, mode);
	}

	unsigned int red;
	unsigned int green;
	unsigned int blue;

	static constexpr size_t argSize = 3;
};

class ColorStructure : public BaseColorStructure
{
public:
	explicit ColorStructure(const Color color, const ColorMode mode = normal) :
		BaseColorStructure(mode), color(color) {}

	std::string toString() const override {
		return colorToString(color, mode);
	}

	Color color;

	static constexpr size_t argSize = 1;
};
