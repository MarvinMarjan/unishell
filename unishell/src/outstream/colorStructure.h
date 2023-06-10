#pragma once

#include "../utilities/stringUtil.h"

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


constexpr inline Color stringToColor(const std::string& strMode) {
	if (strMode == "std") return null;

	if (strMode == "red") return red;
	if (strMode == "green") return green;
	if (strMode == "yellow") return yellow;
	if (strMode == "blue") return blue;
	if (strMode == "purple") return purple;
	if (strMode == "cyan") return cyan;
	if (strMode == "white") return white;

	if (strMode == "gray") return gray;
	if (strMode == "wred") return wred;
	if (strMode == "wgreen") return wgreen;
	if (strMode == "wyellow") return wyellow;
	if (strMode == "wblue") return wblue;
	if (strMode == "wpurple") return wpurple;
	if (strMode == "wcyan") return wcyan;

	return null;
}

constexpr inline ColorMode stringToColorMode(const std::string& strMode) {
	if (strMode == "normal") return normal;
	if (strMode == "dark") return dark;
	if (strMode == "italic") return italic;
	if (strMode == "underline") return underline;
	if (strMode == "crossed") return crossed;

	return normal;
}



// returns the color assigned to the id (0 - 255)
constexpr inline std::string id(const unsigned int i, const ColorMode mode) noexcept {
	return "\033[" + tostr((int)mode) + ";38;5;" + tostr(i) + 'm';
}

// returns rgb ANSI notation
constexpr inline std::string rgb(const unsigned int red, const unsigned int green, const unsigned int blue, const ColorMode mode) noexcept {
	return "\033[" + tostr((int)mode) + ";38;2;" + tostr(red) + ';' + tostr(green) + ';' + tostr(blue) + 'm';
}

constexpr inline std::string colorToString(const Color color, const ColorMode mode) noexcept {
	return "\033[" + tostr((int)mode) + ';' + tostr((int)color) + 'm';
}


class BaseColorStructure
{
public:
	virtual ~BaseColorStructure() = default;
	explicit constexpr inline BaseColorStructure(const ColorMode mode = normal) : mode(mode) {}

	virtual constexpr inline std::string toString() const = 0;

	ColorMode mode;
};

class IdColorStructure : public BaseColorStructure
{
public:
	constexpr inline explicit IdColorStructure(const unsigned int idc, const ColorMode mode = normal) : BaseColorStructure(mode), idc(idc) {}

	constexpr std::string toString() const override {
		return id(idc, mode);
	}

	unsigned int idc;

	static constexpr size_t argSize = 1;
};

class RGBColorStructure : public BaseColorStructure
{
public:
	constexpr inline RGBColorStructure(const unsigned int red, const unsigned int green, const unsigned int blue, const ColorMode mode = normal) :
		BaseColorStructure(mode), red(red), green(green), blue(blue) {}

	constexpr std::string toString() const override {
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
	explicit constexpr inline ColorStructure(const Color color, const ColorMode mode = normal) :
		BaseColorStructure(mode), color(color) {}

	constexpr std::string toString() const override {
		return colorToString(color, mode);
	}

	Color color;

	static constexpr size_t argSize = 1;
};
