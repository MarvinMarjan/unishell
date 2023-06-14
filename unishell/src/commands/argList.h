#pragma once

#include "../data/type.h"

class ArgList : public std::vector<LiteralValue*>
{
public:
	ArgList() {}

	explicit ArgList(const TokenList& tokens) {
		for (const Token& val : tokens)
			push_back(val.getLiteral());
	}

	explicit ArgList(const Token& list) {
		for (LiteralValue* val : asList(list.getLiteral()))
			push_back(val);
	}
};
