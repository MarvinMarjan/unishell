#pragma once

#include <iostream>
#include <iomanip>

#include "stringUtil.h"

#include "../parser/expression/type.h"

#define litToStr TypeUtil::literalValueToString

class TypeUtil
{
public:
	static inline bool isBoolean(const std::string& strBool) noexcept {
		return (strBool == "true" || strBool == "false");
	}

	static inline std::string boolToString(bool boolean) {
		return (boolean) ? "true" : "false";
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

		return text.str();
	}

	static inline std::string literalValueToString(LiteralValue* val) {
		if (!val) return std::string("null");

		if (val->index() == 0) return asStr(val);
		else if (val->index() == 1) return formatDouble(asDbl(val), 2);
		else if (val->index() == 2) return boolToString(asBool(val));

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
};