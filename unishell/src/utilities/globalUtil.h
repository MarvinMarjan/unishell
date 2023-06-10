#pragma once

#include "../parser/instream/token.h"

class GlobalUtil
{
public:
	constexpr static TokenEnum keywordToToken(const std::string& keyword) noexcept {
		if (keyword == "and") return AND;
		if (keyword == "or") return OR;
		if (keyword == "null") return NULLVAL;

		return LITERAL;
	}
};