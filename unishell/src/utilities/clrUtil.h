#pragma once

#include "../outstream/outputColor.h"

#include <regex>

class ClrUtil
{
public:
	static inline std::string getColoredColorList() noexcept {
		std::string str = "";

		for (size_t i = 0; i < __color.size(); i++)
			str += clr(__color[i], stringToColor(__color[i])) + ((i + 1 < __color.size()) ? "\n" : "");

		return str;
	}

	static inline std::string getColoredIdColorList() noexcept {
		std::stringstream str;

		for (unsigned int i = 0, col = 1; i <= 255; i++) {
			str << id(i, normal) << std::setw(3) << std::left << tostr(i) << endclr << ((i + 1 <= 255) ? " " : "");

			if (++col > 21) {
				str << "\n";
				col = 1;
			}
		}

		return str.str();
	}

	static inline std::string getColoredColorModeList() noexcept {
		std::string str = "";

		for (size_t i = 0; i < __colormode.size(); i++)
			str += clr(__colormode[i], white, stringToColorMode(__colormode[i])) + ((i + 1 < __colormode.size()) ? "\n" : "");

		return str;
	}
};