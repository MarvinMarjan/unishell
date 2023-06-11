#pragma once

#include "../outstream/color/colorChars.h"

class ClrUtil
{
public:
	// returns a string containing every color in __color
	static std::string getColoredColorList() noexcept {
		std::string str = "";

		for (size_t i = 0; i < __color.size(); i++)
			str += clr(__color[i], stringToColor(__color[i])) + ((i + 1 < __color.size()) ? "\n" : "");

		return str;
	}

	// returns a string containing a table of 255 ANSI colors
	static std::string getColoredIdColorList() noexcept {
		std::stringstream str;

		for (size_t i = 0, col = 1; i <= 255; i++) {
			str << id((unsigned int)i, normal) << std::setw(3) << std::left << tostr(i) << endclr << ((i + 1 <= 255) ? " " : "");

			if (++col > 21) {
				str << "\n";
				col = 1;
			}
		}

		return str.str();
	}

	// returns a string containing every color mode in __colormode
	static std::string getColoredColorModeList() noexcept {
		std::string str = "";

		for (size_t i = 0; i < __colormode.size(); i++)
			str += clr(__colormode[i], white, stringToColorMode(__colormode[i])) + ((i + 1 < __colormode.size()) ? "\n" : "");

		return str;
	}
};