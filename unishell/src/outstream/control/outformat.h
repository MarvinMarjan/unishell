#pragma once

#include "../../algorithm/regex/match.h"
#include "../../color/structure/color_structure.h"

#include <string>


extern const std::string __regex_color_escape_char_pattern;


// raw: the size of the rawStr
// clr: the size of the color escape chars
struct ColorizedStringSize {
	std::string raw_str;

	int raw_size;
	int clr_size;
};

// returns a ColorizedStringSize based on "src"
ColorizedStringSize getColorizedStringSize(const std::string& src) noexcept;

// if "src.size" is greater than "maxLen", then
// get a substring of 0 and "maxLen" and completes it with "..."
inline std::string truncateString(const std::string& src, const size_t max_len, const bool endcl = true) {
	const ColorizedStringSize src_sizes = getColorizedStringSize(src);

	if (src_sizes.raw_size <= max_len)
		return src;
	else
		return src.substr(0, max_len + src_sizes.clr_size - 3) + "..." + ((!endcl) ? "" : endclr);
} 