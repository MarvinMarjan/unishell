#pragma once

#include "../system/global.h"

#include "colorStructure.h"

// predefined color
inline std::string clr(const std::string& text, Color color = null, ColorMode mode = normal) noexcept {
	return colorToString(color, mode) + text + endclr;
}

// id color
inline std::string clr(const std::string& text, unsigned int i, ColorMode mode = normal) noexcept {
	return id(i, mode) + text + endclr;
}

// rgb color
inline std::string clr(const std::string& text, const std::vector<unsigned int>& rgbVec = {0, 0, 0}, ColorMode mode = normal) noexcept {
	return rgb(rgbVec[0], rgbVec[1], rgbVec[2], mode) + text + endclr;
}

inline std::string clr(const std::string& text, const std::string& strColor) noexcept {
	return strColor + text + endclr;
}



inline std::string qtd(const std::string& text) noexcept {
	return clr('\"' + text + '\"', __clr_quoted->toString());
}

inline std::string idformat(const std::string& text) noexcept {
	return clr(text, __clr_identifier->toString());
}

inline std::string boolformat(const std::string& text) noexcept {
	return clr(text, __clr_boolean->toString());
}

inline std::string numformat(const std::string& text) noexcept {
	return clr(text, __clr_numbers->toString());
}

inline std::string nullformat(const std::string& text) noexcept {
	return clr(text, __clr_keyword->toString());
}