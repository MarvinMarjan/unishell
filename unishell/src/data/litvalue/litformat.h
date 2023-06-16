#pragma once

#include "type.h"

#include "../../system/global/typedecl.h"
#include "../../instream/scanner/token.h"

#define litToStr lit::literalValueToString


namespace lit
{


	inline std::string boolToString(const bool boolean, const bool color = false) noexcept {
		const std::string strBool = ((boolean) ? "true" : "false");
		return (color) ? boolformat(strBool) : strBool;
	}

	constexpr inline bool stringToBool(const std::string& boolStr) noexcept {
		return (boolStr == "true") ? true : false;
	}


	// returns a string that represents a double value.
	// returns a integer string if the value can be simplified
	std::string formatDouble(const double value, const bool color = false) noexcept;


	// returns a string that represents the value of a List.
	// List( item1, item2, ... )
	std::string formatList(LiteralValue* lit) noexcept;


	// returns a string that represents the value of a Object.
	// Object( key: value )
	std::string formatObject(LiteralValue* lit) noexcept;


	// returns a string that represents a LiteralValue.
	std::string literalValueToString(LiteralValue* val, const bool color = false) noexcept;



	inline LitList stringListToLiteralList(const StringList& list) noexcept {
		LiteralValue::List res;
		
		for (const std::string& item : list)
			res.push_back(lit(item));

		return res;
	}



	std::string colorizeStrType(const std::string& type) noexcept;

	TokenEnum typeToTokenEnum(const LiteralValue::Type type) noexcept;
	std::string getTypeAsString(const LiteralValue::Type type, const bool colorize = false) noexcept;



	inline Token literalToToken(LiteralValue* lit) noexcept {
		return Token(typeToTokenEnum(lit->type()), "", lit, {}, 0);
	}

	inline TokenEnum getLitTokenEnum(LiteralValue* lit) noexcept {
		return typeToTokenEnum(lit->type());
	}



	inline std::string getTypeAsString(const std::vector<LiteralValue::Type>& types, const bool colorize = false) noexcept {
		std::string str = "";

		for (size_t i = 0; i < types.size(); i++)
			str += getTypeAsString(types[i], colorize) + ((i + 1 >= types.size()) ? "" : " | ");

		return str;
	}


}