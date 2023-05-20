#pragma once

#include "../parser/instream/token.h"

class GlobalUtil
{
public:
	static inline TokenEnum keywordToToken(const std::string& keyword) {
		if (keyword == "and") return AND;
		if (keyword == "or") return OR;

		return LITERAL;
	}
};