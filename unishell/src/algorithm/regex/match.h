#pragma once

#include "../../system/global/typedecl.h"

#include <regex>


namespace alg
{

namespace regex
{
	

	// return a list containing every match of "pattern" in "src"
	inline StringList getMatchesAsStringList(const std::string& src, const std::regex& pattern) {
		std::sregex_iterator it(src.begin(), src.end(), pattern, std::regex_constants::match_default | std::regex_constants::match_any);
		std::sregex_iterator end;

		StringList matches;

		for (; it != end; it++)
			matches.push_back(it->str());

		return matches;
	}


} // namespace regex

} // namespace alg