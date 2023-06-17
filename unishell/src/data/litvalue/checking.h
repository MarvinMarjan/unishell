#pragma once

#include "type.h"

#include <cmath>

namespace lit
{


	constexpr inline bool isBoolean(const std::string& strBool) noexcept {
		return (strBool == "true" || strBool == "false");
	}

	// returns true if a double value can be
	// represented as a integer (1.0, 3.0, ...)
	inline bool isIntNumber(const double value) noexcept {
		return (value == std::round(value));
	}
	
	inline bool isTypeof(LiteralValue* value, const LiteralValue::Type type) noexcept {
		return (value->type() == type);
	}

	inline void checkNull(LiteralValue* value) noexcept {
		if (!value)
			*value = LiteralValue("null");
	}

	// return true if all values inside "list" has type "type"
	inline bool isListOf(LiteralValue* list, const LiteralValue::Type type) {
		if (list->type() != LiteralValue::Type::List) return false;
		
		for (LiteralValue* val : asList(list))
			if (val->type() != type)
				return false;

		return true;
	}


}
