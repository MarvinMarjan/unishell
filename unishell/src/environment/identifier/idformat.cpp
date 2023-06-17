#include "idformat.h"


FormatedIdentifierData formatIdentifier(const Identifier& identifier)
{
	const std::string name = identifier.getName();
	const std::string strVal = litToStr(identifier.getValue(), true);
	const std::string type = lit::getTypeAsString(identifier.getType(), true);

	return {
		.name = clr(name, (identifier.isSysId()) ? __clr_sys_identifier->toString() : __clr_identifier->toString()),
		.value = strVal,
		.type = type
	};
}


std::string formatedIdentifierDataToString(const FormatedIdentifierData& data) noexcept
{
	std::stringstream str;

	ColorizedStringSize strSizes = getColorizedStringSize(data.name);
	str << std::setw(strSizes.clr_size + 17) << std::left << truncateString(data.name, 12);

	strSizes = getColorizedStringSize(data.type);
	str << std::setw(strSizes.clr_size + 10) << std::left << data.type;
	str << "  ";

	strSizes = getColorizedStringSize(data.value);
	str << ((strSizes.raw_size > 60) ? "..." : data.value);

	return str.str();
}