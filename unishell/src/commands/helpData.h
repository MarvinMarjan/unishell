#pragma once

#include "../utilities/typeUtil.h"

struct HDParam
{
	std::string name;
	IdValueTypeList types;
	bool optional = false;
};

struct HDFlag
{
	std::string name;
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

inline std::string stringifyHelpData(const CommandHelpData& data, BaseColorStructure* cmdClr = __clr_command, bool nameOnly = false) noexcept {
	std::stringstream str;

	str << clr(data.name, cmdClr->toString());
	
	if (nameOnly) return str.str();

	for (const HDParam& param : data.params)
		str << " [ " << clr(param.name, __clr_help_param_name->toString()) << ((param.optional) ? clr("?", __clr_help_optional->toString()) : "") << ": " << stringifyParamTypes(param.types, true) << " ]";

	if (data.undefinedParamSize)
		str << clr("...", __clr_help_undefined_param_size->toString());

	for (const HDFlag& flag : data.flags)
		str << " { " << clr(flag.name, __clr_flag->toString()) << " } ";

	str << std::endl << clr("->", 156) << "  " << data.description;

	return str.str();
}