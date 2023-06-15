#pragma once

#include "../system/global/typedecl.h"

#include <regex>

class RegexUtil
{
public:
	static StringList getMatchesAsStringList(const std::string& src, const std::regex& pattern) {
		std::sregex_iterator it(src.begin(), src.end(), pattern, std::regex_constants::match_default | std::regex_constants::match_any);
		std::sregex_iterator end;

		StringList matches;

		for (; it != end; it++)
			matches.push_back(it->str());

		return matches;
	}
};