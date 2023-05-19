#pragma once

#include "../utilities/stringUtil.h"
#include "../system/global.h"

#include "colorStructure.h"

#define tostr std::to_string
#define endclr "\033[0m"


inline std::string colorToString(Color color, ColorMode mode) noexcept;
inline std::string rgb(unsigned int red, unsigned int green, unsigned int blue, ColorMode mode = normal) noexcept;
inline std::string id(unsigned int i, ColorMode mode = normal) noexcept;


// predefined color
inline std::string clr(const std::string& text, Color color = null, ColorMode mode = normal) noexcept {
	return colorToString(color, mode) + text + endclr;
}

// id color
inline std::string clr(const std::string& text, unsigned int i, ColorMode mode = normal) {
	return id(i, mode) + text + endclr;
}

// rgb color
inline std::string clr(const std::string& text, std::vector<unsigned int> rgbVec, ColorMode mode = normal) {
	return rgb(rgbVec[0], rgbVec[1], rgbVec[2], mode) + text + endclr;
}

// only id supported
inline std::string clr(const std::string& text, ColorStructure color) {
	return id(color.id, color.mode) + text + endclr;
}

// returns the color assigned to the id (0 - 255)
inline std::string id(unsigned int i, ColorMode mode) noexcept {
	return "\033[" + tostr((int) mode) + ";38;5;" + tostr(i) + 'm';
}

inline std::string id(ColorStructure color) noexcept {
	return "\033[" + tostr((int)color.mode) + ";38;5;" + tostr(color.id) + 'm';
}

// returns rgb ANSI notation
inline std::string rgb(unsigned int red, unsigned int green, unsigned int blue, ColorMode mode) noexcept {
	return "\033[" + tostr((int) mode) + ";38;2;" + tostr(red) + ';' + tostr(green) + ';' + tostr(blue) + 'm';
}

inline std::string colorToString(Color color, ColorMode mode) noexcept {
	return "\033[" + tostr((int) mode) + ';' + tostr((int) color) + 'm';
}


// put a string inside quotes
inline std::string qtd(const std::string& text) {
	return clr('\"' + text + '\"', __clr_quoted);
}