#pragma once

#include "../system/global.h"

#include "colorStructure.h"

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

inline std::string clr(const std::string& text, const std::string& strColor) {
	return strColor + text + endclr;
}

// put a string inside quotes
inline std::string qtd(const std::string& text) {
	return clr('\"' + text + '\"', __clr_quoted->toString());
}

inline std::string idformat(const std::string& text) {
	return clr(text, __clr_identifier->toString());
}