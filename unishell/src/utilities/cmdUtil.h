#pragma once

#include "../commands/argList.h"
#include "../commands/flagList.h"
#include "../base/commandBaseCore.h"

class CmdUtil
{
public:
	static inline ArgList getArgs(const TokenList& input, bool encapsulate = true, bool firstIsCommand = true, bool* hasExplicitList = nullptr) {
		size_t index = (firstIsCommand) ? 1 : 0;

		if (input.size() <= index) return ArgList(); // has no args

		if (encapsulate) {
			size_t i = index;
			for (i; i < input.size(); i++) {}
			return ArgList(TokenList(input.begin() + index, input.begin() + i));
		}

		else if (input[index].getType() == LIST) {
			if (hasExplicitList != nullptr)
				*hasExplicitList = true;

			return ArgList(input[index]);
		}

		return ArgList();
	}

	static inline FlagList getFlags(const TokenList& input) {
		FlagList flags;

		for (const Token& token : input)
			if (token.getType() == FLAG)
				flags.push_back(Flag{ token.getLexical().substr(1) });

		return flags;
	}

	static inline TokenList removeFlags(const TokenList& input) {
		TokenList rmvdFlags;

		for (const Token& token : input)
			if (token.getType() != FLAG)
				rmvdFlags.push_back(token);

		return rmvdFlags;
	}

	static std::string getAllCmdHelpMessage(bool nameOnly = false);
	static std::string getAllRetCmdHelpMessage(bool nameOnly = false);

	static CommandBase* getCommand(const std::string& cmdName, ArgList args, FlagList flags);
	static RetCommandBase* getRetCommand(const std::string& cmdName, ArgList args, FlagList flags);
};
