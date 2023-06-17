#pragma once

#include "../../data/litvalue/type.h"
#include "flags.h"

class RetCommandBase;


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


// get the args of a command from TokenList
ArgList getArgs(const TokenList& input, const bool encapsulate = true, const bool firstIsCommand = true, bool* hasExplicitList = nullptr);



// some commands can have the same name, but
// different parameters. use this function to get the
// right command based on its arguments

template <typename T>
inline RetCommandBase* checkArgOverloadImpl(RetCommandBase* cmd, const ArgList& args, const FlagList& flags) {
	if (cmd)
		return cmd;

	try {
		cmd = new T(args, flags);
	}
	catch (...) {
		return nullptr;
	}

	return cmd;
}

template <typename... Ts>
inline RetCommandBase* checkArgOverload(const ArgList& args, const FlagList& flags) {
	RetCommandBase* cmd = nullptr;

	// fold expression
	cmd = (..., (cmd = checkArgOverloadImpl<Ts>(cmd, args, flags)));

	return cmd;
}