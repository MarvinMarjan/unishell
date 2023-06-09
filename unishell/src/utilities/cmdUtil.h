#pragma once

#include "../commands/argList.h"
#include "../commands/flagList.h"
#include "../base/commandBaseCore.h"
#include "../commands/helpData.h"

class CmdUtil
{
public:
	static inline std::string funcToString(CmdFunc func) {
		switch (func) {
		case CmdFunc::Type: return "Type";
		case CmdFunc::Literal: return "Literal";
		case CmdFunc::Number: return "Number";
		case CmdFunc::List: return "List";
		case CmdFunc::Object: return "Object";
		case CmdFunc::System: return "System";
		case CmdFunc::Filesystem: return "Filesystem";

		default: return "unknown";
		}
	}
	
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

	static inline std::string getAllCmdHelpMessage(bool nameOnly = false) {
		std::string msg = "";

		for (CommandBase* cmd : __sys_commands)
			msg += stringifyHelpData(cmd->help(), __clr_command, nameOnly) + ((!nameOnly) ? "\n\n\n" : "\n");

		return msg;
	}

	static inline std::string getAllRetCmdHelpMessage(bool nameOnly = false) {
		std::string msg = "";

		for (RetCommandBase* cmd : __sys_ret_commands)
			msg += stringifyHelpData(cmd->help(), __clr_sys_ret_command, nameOnly) + ((!nameOnly) ? "\n\n\n" : "\n");

		return msg;
	}

	template <typename T>
	static inline StringList cmdListToStr(std::vector<T*> list) {
		StringList strList;

		for (T* item : list)
			strList.push_back(item->symbol);

		return strList;
	}


	static CommandBase* getCommand(const std::string& cmdName, ArgList args, FlagList flags);

	static inline CommandBase* getCommand(const std::string& cmdName) {
		for (CommandBase* cmd : __sys_commands)
			if (cmdName == cmd->symbol)
				return cmd;

		return nullptr;
	}

	static RetCommandBase* getRetCommand(const std::string& cmdName, ArgList args, FlagList flags);

	static inline RetCommandBase* getRetCommand(const std::string& cmdName) {
		for (RetCommandBase* cmd : __sys_ret_commands)
			if (cmdName == cmd->symbol)
				return cmd;

		return nullptr;
	}



	template <typename T>
	static inline RetCommandBase* checkArgOverloadImpl(RetCommandBase* cmd, ArgList args, FlagList flags) {
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
	static inline RetCommandBase* checkArgOverload(ArgList args, FlagList flags) {
		RetCommandBase* cmd = nullptr;

		// fold expression
		cmd = (..., (cmd = checkArgOverloadImpl<Ts>(cmd, args, flags)));

		return cmd;
	}
};
