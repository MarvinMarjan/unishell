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

	static inline std::string formatDouble(double value, unsigned short precision) {
		std::stringstream text;

		if (isInteger(value))
			text << std::to_string(static_cast<int>(value));

		else
			text << std::fixed << std::setprecision(precision) << value;

		return ((color) ? numformat(text.str()) : text.str());
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

	static inline std::string literalValueToString(LiteralValue* val, bool color = false) {
		if (!val) return std::string("null");

		TypeUtil::color = color;

		if (val->index() == 0) return ((color) ? qtd(asStr(val)) : asStr(val));
		else if (val->index() == 1) return formatDouble(asDbl(val), 2);
		else if (val->index() == 2) return boolToString(asBool(val));
		else if (val->index() == 3) return formatList(val);

		return std::string();
	}

	static inline TokenEnum getTypeAsTokenEnum(IdValueType type) noexcept {
		switch (type) {
		case Literal: return LITERAL;
		case Number: return NUMBER;
		case Bool: return BOOLEANVAL;
		case Null: return NULLVAL;
		}

		return LITERAL;
	}

	static inline bool isTypeof(LiteralValue* value, IdValueType type) {
		return (getValueActiveType(value) == type);
	}

	static inline void checkNull(LiteralValue* value) {
		if (!value)
			value = new LiteralValue("null");
	}

private:
	static bool color;
};