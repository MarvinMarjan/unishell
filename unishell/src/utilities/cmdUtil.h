#pragma once

#include "../commands/argList.h"
#include "../commands/flagList.h"
#include "../base/commandBaseCore.h"
#include "../commands/helpData.h"

class CmdUtil
{
public:
	static inline ArgList getArgs(const TokenList& input, bool encapsulate = true, bool firstIsCommand = true, bool* hasExplicitList = nullptr) {
		const size_t index = (firstIsCommand) ? 1 : 0;

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

	static inline std::string getAllCmdHelpMessage(bool nameOnly = false) {
		std::string msg = "";

		for (const std::string& cmdName : __sys_commands)
			msg += stringifyHelpData(getCommand(cmdName)->help(), __clr_command, nameOnly) + ((!nameOnly) ? "\n\n\n" : "\n");

		return msg;
	}

	static inline std::string getAllRetCmdHelpMessage(bool nameOnly = false) {
		std::string msg = "";

		for (const std::string& cmdName : __sys_ret_commands)
			msg += stringifyHelpData(getRetCommand(cmdName)->help(), __clr_sys_ret_command, nameOnly) + ((!nameOnly) ? "\n\n\n" : "\n");

		return msg;
	}


	static CommandBase* getCommand(const std::string& cmdName);
	static CommandBase* getCommand(const std::string& cmdName, ArgList args, FlagList flags);
	static RetCommandBase* getRetCommand(const std::string& cmdName, ArgList args, FlagList flags);
	static RetCommandBase* getRetCommand(const std::string& cmdName);
};
