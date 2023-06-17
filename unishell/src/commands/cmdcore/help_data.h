#pragma once

#include "../../system/global/global.h"
#include "../../data/litvalue/type.h"
#include "../../base/command_base_core.h"

struct HDParam
{
	std::string name;
	lit::LitTypeList types;
	bool optional = false;
};

struct HDFlag
{
	std::string name;
	std::string meaning;
};


using HDParamList = std::vector<HDParam>;
using HDFlagList  = std::vector<HDFlag>;


struct CommandHelpData
{
	std::string name;

	HDParamList params;
	bool undefinedParamSize = false;

	std::string description;

	HDFlagList flags;

};

// replaces ^N by the param name located at N index
std::string formatDescription(const std::string& description, const HDParamList& params);


std::string stringifyHelpData(const CommandHelpData& data, BaseColorStructure* cmdClr = __clr_command, const bool nameOnly = false) noexcept;



inline std::string getAllCmdHelpMessage(const bool nameOnly = false) noexcept {
	std::string msg = "";

	for (CommandBase* cmd : __sys_commands)
		msg += stringifyHelpData(cmd->help(), funcToColor(cmd->function), nameOnly) + ((!nameOnly) ? "\n\n\n" : "\n");

	return msg;
}

inline std::string getAllRetCmdHelpMessage(const bool nameOnly = false) noexcept {
	std::string msg = "";

	for (RetCommandBase* cmd : __sys_ret_commands)
		msg += stringifyHelpData(cmd->help(), funcToColor(cmd->function), nameOnly) + ((!nameOnly) ? "\n\n\n" : "\n");

	return msg;
}