#pragma once

#include <iostream>
#include <iomanip>

#include "../data/type.h"
#include "../outstream/control/controlChars.h"

#define litToStr TypeUtil::literalValueToString

class TypeUtil
{
public:
	constexpr static bool isBoolean(const std::string& strBool) noexcept {
		return (strBool == "true" || strBool == "false");
	}

	constexpr static std::string boolToString(const bool boolean) noexcept {
		const std::string strBool = ((boolean) ? "true" : "false");
		return (color) ? boolformat(strBool) : strBool;
	}

	constexpr static bool stringToBool(const std::string& boolStr) noexcept {
		return (boolStr == "true") ? true : false;
	}

	// returns true if a double value can be
	// represented as a integer (1.0, 3.0, ...)
	static bool isInteger(const double value) noexcept {
		return (value == std::round(value));
	}

	// returns a string that represents a double value.
	// returns a integer string if the value canbe simplified
	static std::string formatDouble(const double value) noexcept {
		std::string strNum = tostr(value);
		size_t pos = strNum.find_last_not_of('0');

		if (pos != std::string::npos && strNum[pos] == '.')
			pos--;

		strNum.erase(pos + 1);

		return ((color) ? numformat(strNum) : strNum);
	}

	// returns a string that represents the value of a List.
	// List( item1, item2, ... )
	static std::string formatList(LiteralValue* lit) noexcept {
		std::stringstream str;

		str << "List( ";

		std::vector<LiteralValue*> list = asList(lit);

		for (size_t i = 0; i < list.size(); i++)
			str << litToStr(list[i], true) << ((i + 1 < list.size()) ? ", " : "");

		str << " )";

		return str.str();
	}

	// returns a string that represents the value of a Object.
	// Object( key: value )
	static std::string formatObject(LiteralValue* lit) noexcept {
		std::stringstream str;

		str << "Object( ";

		std::map<std::string, LiteralValue*> obj = asObj(lit);

		auto objEnd = obj.end();

		if (obj.size() > 0) objEnd--;

		for (auto it = obj.begin(); it != obj.end(); it++)
			str << it->first << ": " << litToStr(it->second, true) << ((it != objEnd) ? ", " : "");

		str << " )";

		return str.str();
	}

	// returns a string that represents a LiteralValue.
	static std::string literalValueToString(LiteralValue* val, const bool color = false) noexcept {
		if (!val) return ((color) ? nullformat("null") : "null");

		TypeUtil::color = color;

		if (val->index() == 0) return ((color) ? qtd(asStr(val)) : asStr(val));
		else if (val->index() == 1) return formatDouble(asDbl(val));
		else if (val->index() == 2) return boolToString(asBool(val));
		else if (val->index() == 3) return formatList(val);
		else if (val->index() == 4) return formatObject(val);

		return std::string();
	}

	static LitList stringListToLiteralList(const StringList& list) noexcept {
		LitList res;

		for (const std::string& item : list)
			res.push_back(lit(item));

		return res;
	}

	static Token literalToToken(LiteralValue* lit) noexcept {
		return Token(typeToTokenEnum(lit->type()), "", lit, {}, 0);
	}

	static TokenEnum getLitTokenEnum(LiteralValue* lit) noexcept {
		return typeToTokenEnum(lit->type());
	}

	static constexpr TokenEnum typeToTokenEnum(const LiteralValueType type) noexcept {
		switch (type) {
		case Literal:	return LITERAL;
		case Number:	return NUMBER;
		case Bool:		return BOOLEANVAL;
		case List:		return LIST;
		case Object:	return OBJECT;
		case Null:		return NULLVAL;
		}

		return LITERAL;
	}

	static constexpr std::string getTypeAsString(const LiteralValueType type, const bool colorize = false) noexcept {
		std::string ret;
		
		switch (type) {
		case Literal:	ret = "Literal"; break;
		case Number:	ret = "Number"; break;
		case Bool:		ret = "Bool"; break;
		case List:		ret = "List"; break;
		case Object:	ret = "Object"; break;
		case Null:		ret = "Null"; break;
		case Any:		ret = "Any"; break;

		default: ret = "Unknown";
		}

		if (colorize)
			ret = colorizeStrType(ret);

		return ret;
	}

	static constexpr std::string getTypeAsString(const std::vector<LiteralValueType>& types, const bool colorize = false) noexcept {
		std::string str = "";

		for (size_t i = 0; i < types.size(); i++)
			str += getTypeAsString(types[i], colorize) + ((i + 1 >= types.size()) ? "" : " | ");

		return str;
	}

	static constexpr std::string colorizeStrType(const std::string& type) noexcept {
		if (type == "Literal")		return clr(type, __clr_type_literal->toString());
		else if (type == "Number")	return clr(type, __clr_type_number->toString());
		else if (type == "Bool")	return clr(type, __clr_type_bool->toString());
		else if (type == "List")	return clr(type, __clr_type_list->toString());
		else if (type == "Object")	return clr(type, __clr_type_object->toString());
		else if (type == "Any")		return clr(type, __clr_type_any->toString());

		else return type;
	}
	
	static constexpr bool isTypeof(LiteralValue* value, const LiteralValueType type) noexcept {
		return (value->type() == type);
	}

	// return true if all values inside "list" has type "type"
	static constexpr bool isListOf(LiteralValue* list, const LiteralValueType type) {
		if (list->type() != List) return false;

		for (LiteralValue* val : asList(list))
			if (val->type() != type)
				return false;

		return true;
	}

	static constexpr void checkNull(LiteralValue* value) noexcept {
		if (!value)
			*value = LiteralValue("null");
	}

private:
	static bool color;
};