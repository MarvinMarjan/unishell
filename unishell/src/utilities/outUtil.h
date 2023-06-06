#pragma once

#include "../outstream/outputColor.h"
#include "regexUtil.h"

class OutUtil
{
public:
	struct ColorizedStringSize {
		std::string rawStr;
		int raw;
		int clr;
	};

	static inline ColorizedStringSize getColorizedStringSize(const std::string& src) {
		std::string copy = std::regex_replace(src, std::regex(__regex_color_escape_char_pattern), "", std::regex_constants::format_default | std::regex_constants::match_any);

		int clrSize = 0;

		for (const std::string& item : RegexUtil::getMatches(src, std::regex(__regex_color_escape_char_pattern)))
			clrSize += (int)item.size();

		return { .rawStr = copy, .raw = (int)copy.size(), .clr = clrSize };
	}

	static inline std::string truncateString(const std::string& src, size_t maxLen, bool endClr = true) {
		ColorizedStringSize srcSizes = getColorizedStringSize(src);
		
		if (srcSizes.rawStr.size() <= maxLen)
			return src;

		else
			return src.substr(0, maxLen + srcSizes.clr - 3) + "..." + ((endClr) ? endclr : "");
	}
};
