#pragma once

#include "../data/type.h"

class ArgList : public std::vector<LiteralValue*>
{
public:
	ArgList() {}

	explicit constexpr inline ArgList(const TokenList& tokens) {
		for (Token val : tokens)
			push_back(val.getLiteral());
	}

	explicit constexpr inline ArgList(const Token& list) {
		for (LiteralValue* val : asList(list.getLiteral()))
			push_back(val);
	}
};
