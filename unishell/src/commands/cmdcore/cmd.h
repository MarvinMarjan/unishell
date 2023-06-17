#pragma once


#include "../../base/command_base_core.h"
#include "../../system/global/global.h"
#include "../../algorithm/vector/item.h"
#include "args.h"
#include "flags.h"


#define CHECK_CMD(cmd) \
	if (cmdName == cmd().symbol) return new cmd(args, flags) \



#define CHECK_CMD_OL(symbol, ...) \
	if (cmdName == symbol) return checkArgOverload<__VA_ARGS__>(args, flags) \



template <typename T>
inline StringList cmdListToStr(const std::vector<T>& list) {
	StringList strList;

	for (T item : list)
		strList.push_back(item->symbol);

	return strList;
}

template <typename T>
inline int getCommandCount(const std::vector<T>& list, const std::string& cmdName) noexcept {
	return (int)alg::vector::findAll(cmdListToStr(list), cmdName).size();
}


template <typename T>
inline T getCommandFrom(const std::vector<T>& list, const std::string& cmdName) noexcept {
	for (T cmd : list)
		if (cmdName == cmd->symbol)
			return cmd;

	return nullptr;
}


template <typename T>
inline BaseColorStructure* getCommandColor(const std::vector<T>& list, const std::string& cmdName) {
	const T cmd = getCommandFrom(list, cmdName);

	if (getCommandCount(list, cmdName) > 1)
		return __clr_multi_command;

	else if (cmd)
		return funcToColor(cmd->function);

	else
		return __clr_command;
}


// return a CommandBase* according to "cmdName"
CommandBase* getCommand(const std::string& cmdName, const ArgList& args, const FlagList& flags);

inline CommandBase* getCommand(const std::string& cmdName) noexcept {
	for (CommandBase* cmd : __sys_commands)
		if (cmdName == cmd->symbol)
			return cmd;

	return nullptr;
}

// return a RetCommandBase* according to "cmdName"
RetCommandBase* getRetCommand(const std::string& cmdName, const ArgList& args, const FlagList& flags);

inline RetCommandBase* getRetCommand(const std::string& cmdName) noexcept {
	for (RetCommandBase* cmd : __sys_ret_commands)
		if (cmdName == cmd->symbol)
			return cmd;

	return nullptr;
}