#pragma once

#include "../outstream/color/colorChars.h"
#include "regexUtil.h"

class OutUtil
{
public:
	
	// raw: the size of the rawStr
	// clr: the size of the color escape chars
	struct ColorizedStringSize {
		std::string rawStr;
		int raw;
		int clr;
	};

	// returns a ColorizedStringSize based on "src"
	static ColorizedStringSize getColorizedStringSize(const std::string& src) noexcept {
		const std::string copy = std::regex_replace(src, std::regex(__regex_color_escape_char_pattern), "", std::regex_constants::format_default | std::regex_constants::match_any);

		int clrSize = 0;

		for (const std::string& item : RegexUtil::getMatchesAsStringList(src, std::regex(__regex_color_escape_char_pattern)))
			clrSize += (int)item.size();

		return { .rawStr = copy, .raw = (int)copy.size(), .clr = clrSize };
	}

	// if "src.size" is greater than "maxLen", then
	// get a substring of 0 and "maxLen" and completes it with "..."
	static std::string truncateString(const std::string& src, const size_t maxLen, const bool endClr = true) {
		const ColorizedStringSize srcSizes = getColorizedStringSize(src);
		
		if (srcSizes.rawStr.size() <= maxLen)
			return src;

		else
			return src.substr(0, maxLen + srcSizes.clr - 3) + "..." + ((endClr) ? endclr : "");
	}
};
