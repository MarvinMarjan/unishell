#pragma once

#include "../utilities/stringUtil.h"
#include "../system/global/global.h"
#include "../data/type.h"

struct HDParam
{
	std::string name;
	LiteralValueTypeList types;
	bool optional = false;
};

struct HDFlag
{
	std::string name;
	std::string meaning;
};

typedef std::vector<HDParam> HDParamList;
typedef std::vector<HDFlag> HDFlagList;

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