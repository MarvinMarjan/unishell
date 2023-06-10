#pragma once

#include "../utilities/typeUtil.h"

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
inline std::string formatDescription(const std::string& description, const HDParamList& params) {
	std::string fDescription = "";

	for (size_t i = 0; i < description.size(); i++) {
		if (description[i] == '^' && i + 1 < description.size() && StringUtil::isDigit(description[i + 1])) {
			const int paramIndex = std::stoi(StringUtil::charToStr(description[i + 1]));
			const std::string paramName = params[paramIndex].name;


			fDescription += clr(paramName, __clr_help_param_name->toString());
			i++;
		}

		else
			fDescription += description[i];
	}

	return fDescription;
}


inline std::string stringifyHelpData(const CommandHelpData& data, BaseColorStructure* cmdClr = __clr_command, bool nameOnly = false) noexcept {
	std::stringstream str;

	str << clr(data.name, cmdClr->toString());
	
	if (nameOnly) return str.str();

	for (const HDParam& param : data.params)
		str << " [ " << clr(param.name, __clr_help_param_name->toString()) << ((param.optional) ? clr("?", __clr_help_optional->toString()) : "") << ": " << stringifyParamTypes(param.types, true) << " ]";

	if (data.undefinedParamSize)
		str << clr("...", __clr_help_undefined_param_size->toString());

	for (const HDFlag& flag : data.flags)
		str << " { " << clr(flag.name, __clr_flag->toString()) << " (" << clr(flag.meaning, __clr_help_flag_meaning->toString()) << ") " << "} ";

	str << std::endl << clr("->", 156) << "  " << formatDescription(data.description, data.params);

	return str.str();
}