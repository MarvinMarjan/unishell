#pragma once

#include <iostream>
#include <iomanip>

#include "stringUtil.h"

#include "../parser/expression/type.h"
#include "../outstream/outputColor.h"

#define litToStr TypeUtil::literalValueToString

class TypeUtil
{
public:
	static inline bool isBoolean(const std::string& strBool) noexcept {
		return (strBool == "true" || strBool == "false");
	}

	static inline std::string boolToString(bool boolean) {
		if (color) return boolformat(((boolean) ? "true" : "false"));
		else return ((boolean) ? "true" : "false");
	}

	static inline bool stringToBool(const std::string& boolStr) noexcept {
		return (boolStr == "true") ? true : false;
	}

	static inline bool isInteger(double value) {
		return (value == std::round(value));
	}

	static inline std::string formatDouble(double value) {
		std::string strNum = tostr(value);
		size_t pos = strNum.find_last_not_of('0');

		if (pos != std::string::npos && strNum[pos] == '.')
			pos--;

		strNum.erase(pos + 1);

		return ((color) ? numformat(strNum) : strNum);
	}

	static inline std::string formatList(LiteralValue* lit) {
		std::stringstream str;

		str << "List( ";

		std::vector<LiteralValue*> list = asList(lit);

		for (size_t i = 0; i < list.size(); i++)
			str << litToStr(list[i], true) << ((i + 1 < list.size()) ? ", " : "");

		str << " )";

		return str.str();
	}

	static inline std::string formatObject(LiteralValue* lit, bool indent = false) {
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

	static inline std::string literalValueToString(LiteralValue* val, bool color = false) {
		if (!val) return ((color) ? nullformat("null") : "null");

		TypeUtil::color = color;

		if (val->index() == 0) return ((color) ? qtd(asStr(val)) : asStr(val));
		else if (val->index() == 1) return formatDouble(asDbl(val));
		else if (val->index() == 2) return boolToString(asBool(val));
		else if (val->index() == 3) return formatList(val);
		else if (val->index() == 4) return formatObject(val);

		return std::string();
	}

	static inline Token literalToToken(LiteralValue* val) {
		return Token(getTypeAsTokenEnum(getValueType(val)), "", val, {}, 0);	
	}

	static inline TokenEnum getLitTokenEnum(LiteralValue* lit) {
		return getTypeAsTokenEnum(getValueType(lit));
	}

	constexpr static inline TokenEnum getTypeAsTokenEnum(IdValueType type) noexcept {
		switch (type) {
		case Literal: return LITERAL;
		case Number: return NUMBER;
		case Bool: return BOOLEANVAL;
		case List: return LIST;
		case Object: return OBJECT;
		case Null: return NULLVAL;
		}

		return LITERAL;
	}

	static inline std::string getTypeAsString(IdValueType type, bool colorize = false) noexcept {
		std::string ret;
		
		switch (type) {
		case Literal: ret = "Literal"; break;
		case Number: ret = "Number"; break;
		case Bool: ret = "Bool"; break;
		case List: ret = "List"; break;
		case Object: ret = "Object"; break;
		case Null: ret = "Null"; break;
		case Any: ret = "Any"; break;

		default: ret = "Unknown";
		}

		if (colorize)
			ret = colorizeStrType(ret);

		return ret;
	}

	static inline std::string getTypeAsString(std::vector<IdValueType> types, bool colorize = false) noexcept {
		std::string str = "";

		for (size_t i = 0; i < types.size(); i++)
			str += getTypeAsString(types[i], colorize) + ((i + 1 >= types.size()) ? "" : " | ");

		return str;
	}

	static inline std::string colorizeStrType(const std::string& type) {
		if (type == "Literal") return clr(type, __clr_type_literal->toString());
		else if (type == "Number") return clr(type, __clr_type_number->toString());
		else if (type == "Bool") return clr(type, __clr_type_bool->toString());
		else if (type == "List") return clr(type, __clr_type_list->toString());
		else if (type == "Object") return clr(type, __clr_type_object->toString());
		else if (type == "Any") return clr(type, __clr_type_any->toString());

		else return type;
	}

	static inline bool isTypeof(LiteralValue* value, IdValueType type) {
		return (getValueType(value) == type);
	}

	static inline bool isListOf(LiteralValue* list, IdValueType type) {
		if (getValueType(list) != List) return false;

		for (LiteralValue* val : asList(list))
			if (getValueType(val) != type)
				return false;

		return true;
	}

	static inline LiteralValueList stringListToLiteralList(StringList list) {
		LiteralValueList res;

		for (const std::string& item : list)
			res.push_back(litStr(item));

		return res;
	}

	static inline void checkNull(LiteralValue* value) {
		if (!value)
			value = new LiteralValue("null");
	}

private:
	static bool color;
};