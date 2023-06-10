#pragma once

#include "../system/global.h"

#include "colorStructure.h"

// predefined color
constexpr inline std::string clr(const std::string& text, const Color color = null, const ColorMode mode = normal) noexcept {
	return colorToString(color, mode) + text + endclr;
}

// id color
constexpr inline std::string clr(const std::string& text, const unsigned int i, const ColorMode mode = normal) noexcept {
	return id(i, mode) + text + endclr;
}

// rgb color
constexpr inline std::string clr(const std::string& text, const std::vector<unsigned int>& rgbVec = {0, 0, 0}, const ColorMode mode = normal) noexcept {
	return rgb(rgbVec[0], rgbVec[1], rgbVec[2], mode) + text + endclr;
}

constexpr inline std::string clr(const std::string& text, const std::string& strColor) noexcept {
	return strColor + text + endclr;
}



constexpr inline std::string qtd(const std::string& text) noexcept {
	return clr('\"' + text + '\"', __clr_quoted->toString());
}

constexpr inline std::string idformat(const std::string& text) noexcept {
	return clr(text, __clr_identifier->toString());
}

constexpr inline std::string boolformat(const std::string& text) noexcept {
	return clr(text, __clr_boolean->toString());
}

constexpr inline std::string numformat(const std::string& text) noexcept {
	return clr(text, __clr_numbers->toString());
}

constexpr inline std::string nullformat(const std::string& text) noexcept {
	return clr(text, __clr_keyword->toString());
}