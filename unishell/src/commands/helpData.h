#pragma once

#include "../utilities/typeUtil.h"

struct HDParam
{
	std::string name;
	IdValueTypeList types;
	bool optional;
};

typedef std::vector<HDParam> HDParamList;

struct CommandHelpData
{
	std::string name;
	HDParamList params;
	bool undefinedParamSize;

	std::string description;
};

inline std::string stringifyHelpData(const CommandHelpData& data, BaseColorStructure* cmdClr = __clr_command) noexcept {
	std::stringstream str;

	str << clr(data.name, cmdClr->toString());
	
	for (const HDParam& param : data.params)
		str << " [ " << clr(param.name, __clr_help_param_name->toString()) << ((param.optional) ? clr("?", __clr_help_optional->toString()) : "") << ": " << stringifyParamTypes(param.types, true) << " ]";

	if (data.undefinedParamSize)
		str << clr("...", __clr_help_undefined_param_size->toString());

	str << std::endl << clr("->", 156) << "  " << data.description;

	return str.str();
}