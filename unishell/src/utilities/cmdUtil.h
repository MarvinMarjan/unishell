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
		case CmdFunc::Type:			return "Type";
		case CmdFunc::Literal:		return "Literal";
		case CmdFunc::Number:		return "Number";
		case CmdFunc::List:			return "List";
		case CmdFunc::Object:		return "Object";
		case CmdFunc::System:		return "System";
		case CmdFunc::Filesystem:	return "Filesystem";
		case CmdFunc::Regex:	return "Regex";

		default: return "unknown";
		}
	}
	
	static inline BaseColorStructure* funcToColor(CmdFunc func) {
		switch (func) {
		case CmdFunc::Type:			return __clr_type_command;
		case CmdFunc::Literal:		return __clr_literal_command;
		case CmdFunc::Number:		return __clr_number_command;
		case CmdFunc::List:			return __clr_list_command;
		case CmdFunc::Object:		return __clr_object_command;
		case CmdFunc::System:		return __clr_system_command;
		case CmdFunc::Filesystem:	return __clr_filesystem_command;
		case CmdFunc::Regex:		return __clr_regex_command;

		default: return __clr_command;
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
			msg += stringifyHelpData(cmd->help(), CmdUtil::funcToColor(cmd->function), nameOnly) + ((!nameOnly) ? "\n\n\n" : "\n");

		return msg;
	}

	static inline std::string getAllRetCmdHelpMessage(bool nameOnly = false) {
		std::string msg = "";

		for (RetCommandBase* cmd : __sys_ret_commands)
			msg += stringifyHelpData(cmd->help(), CmdUtil::funcToColor(cmd->function), nameOnly) + ((!nameOnly) ? "\n\n\n" : "\n");

		return msg;
	}

	template <typename T>
	static inline StringList cmdListToStr(std::vector<T> list) {
		StringList strList;

		for (T item : list)
			strList.push_back(item->symbol);

		return strList;
	}

	template <typename T>
	static inline unsigned int getCommandCount(std::vector<T> list, const std::string& cmdName) {
		return (unsigned int)VectorUtil::findAll(cmdListToStr(list), cmdName).size();
	}

	template <typename T>
	static inline BaseColorStructure* getCommandColor(std::vector<T> list, const std::string& cmdName) {
		T cmd = getCommandFrom(list, cmdName);

		if (getCommandCount(list, cmdName) > 1)
			return __clr_multi_command;

		else if (cmd)
			return funcToColor(cmd->function);

		else
			return __clr_command;
	}


	static CommandBase* getCommand(const std::string& cmdName, ArgList args, FlagList flags);

	static inline CommandBase* getCommand(const std::string& cmdName) {
		for (CommandBase* cmd : __sys_commands)
			if (cmdName == cmd->symbol)
				return cmd;

		return nullptr;
	}
	
	template <typename T>
	static inline T getCommandFrom(std::vector<T> list, const std::string& cmdName) {
		for (T cmd : list)
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

	// some commands can have the same name, but
	// different parameters. use this function to get the
	// right command based on its arguments

	template <typename... Ts>
	static inline RetCommandBase* checkArgOverload(ArgList args, FlagList flags) {
		RetCommandBase* cmd = nullptr;

		// fold expression
		cmd = (..., (cmd = checkArgOverloadImpl<Ts>(cmd, args, flags)));

		return cmd;
	}
};
