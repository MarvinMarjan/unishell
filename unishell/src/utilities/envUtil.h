#pragma once

#include "../environment/environment.h"
#include "outUtil.h"

class EnvUtil
{
public:
	struct FormatedIdentifierData {
		std::string name;
		std::string value;
		std::string type;
	};

	static inline FormatedIdentifierData formatIdentifier(const Identifier& identifier) {
		std::string name = identifier.getName();
		std::string strVal = litToStr(identifier.getValue(), true);
		std::string type = TypeUtil::getTypeAsString(identifier.getType(), true);

		return { 
			.name = clr(name, (identifier.isSysId()) ? __clr_sys_identifier->toString() : __clr_identifier->toString()),
			.value = strVal,
			.type = type
		};
	}

	static inline std::string formatFIDIntoString(const FormatedIdentifierData& data) {
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