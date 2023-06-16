#include "helpData.h"

#include "../../outstream/color/colorChars.h"
#include "../../algorithm/string/char.h"
#include "params.h"

#include <sstream>

std::string formatDescription(const std::string& description, const HDParamList& params)
{
	std::string fDescription = "";

	for (size_t i = 0; i < description.size(); i++) {
		if (description[i] == '^' && i + 1 < description.size() && alg::string::isDigit(description[i + 1])) {
			const int paramIndex = std::stoi(alg::string::charToStr(description[i + 1]));
			const std::string paramName = params[paramIndex].name;


			fDescription += clr(paramName, __clr_help_param_name->toString());
			i++;
		}

		else
			fDescription += description[i];
	}

	return fDescription;
}


std::string stringifyHelpData(const CommandHelpData& data, BaseColorStructure* cmdClr, const bool nameOnly) noexcept
{
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