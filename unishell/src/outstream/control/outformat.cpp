#include "outformat.h"


ColorizedStringSize getColorizedStringSize(const std::string& src) noexcept
{
	const std::string copy = std::regex_replace(src, std::regex(__regex_color_escape_char_pattern), "", std::regex_constants::format_default | std::regex_constants::match_any);

	int clr_size_ = 0;

	for (const std::string& item : alg::regex::getMatchesAsStringList(src, std::regex(__regex_color_escape_char_pattern)))
		clr_size_ += (int)item.size();

	return {
		.raw_str = copy,
		.raw_size = (int)copy.size(),
		.clr_size = clr_size_
	};
}