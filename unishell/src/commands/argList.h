#pragma once

#include "../utilities/stringUtil.h"
#include "../parser/expression/type.h"
#include "../parser/instream/token.h"

class ArgList : public std::vector<LiteralValue*>
{
public:
	ArgList() {}

	explicit ArgList(const TokenList& tokens) {
		for (Token val : tokens)
			push_back(val.getLiteral());
	}

	explicit ArgList(const Token& list) {
		for (LiteralValue* val : asList(list.getLiteral()))
			push_back(val);
	}
};
