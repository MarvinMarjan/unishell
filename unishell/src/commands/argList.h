#pragma once

#include "../utilities/stringUtil.h"
#include "../parser/expression/type.h"
#include "../parser/instream/token.h"

class ArgList : public std::vector<LiteralValue*>
{
public:
	ArgList() {}

	ArgList(TokenList tokens) {
		for (Token val : tokens)
			push_back(val.getLiteral());
	}

	ArgList(Token list) {
		for (Token val : list.getSub())
			push_back(val.getLiteral());
	}
};
