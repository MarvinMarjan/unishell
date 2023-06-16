#pragma once

#include "../data/litvalue/type.h"

class ArgList : public lit::LitList
{
public:
	ArgList() {}

	explicit ArgList(const TokenList& tokens) {
		for (const Token& val : tokens)
			push_back(val.getLiteral());
	}

	explicit ArgList(const Token& list) {
		for (lit::LiteralValue* val : asList(list.getLiteral()))
			push_back(val);
	}
};
