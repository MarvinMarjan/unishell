#pragma once

#include "../environment/environment.h"
#include "outUtil.h"

class EnvUtil
{
public:

	// contains Identifier data as string
	struct FormatedIdentifierData {
		std::string name;
		std::string value;
		std::string type;
	};

	static FormatedIdentifierData formatIdentifier(const Identifier& identifier) {
		const std::string name = identifier.getName();
		const std::string strVal = litToStr(identifier.getValue(), true);
		const std::string type = TypeUtil::getTypeAsString(identifier.getType(), true);

		return { 
			.name = clr(name, (identifier.isSysId()) ? __clr_sys_identifier->toString() : __clr_identifier->toString()),
			.value = strVal,
			.type = type
		};
	}

	static std::string formatFIDToString(const FormatedIdentifierData& data) noexcept {
		std::stringstream str;

		OutUtil::ColorizedStringSize strSizes = OutUtil::getColorizedStringSize(data.name);
		str << std::setw(strSizes.clr + 17) << std::left << OutUtil::truncateString(data.name, 12);

		strSizes = OutUtil::getColorizedStringSize(data.type);
		str << std::setw(strSizes.clr + 10) << std::left << data.type;
		str << "  ";
		
		strSizes = OutUtil::getColorizedStringSize(data.value);
		str << ((strSizes.rawStr.size() > 60) ? "..." : data.value);

		return str.str();
	}
};