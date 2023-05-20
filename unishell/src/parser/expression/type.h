#pragma once

#include <string>
#include <variant>

#define asStr(pLit)  std::get<std::string>(*pLit)
#define asDbl(pLit)  std::get<double>(*pLit)
#define asBool(pLit) std::get<bool>(*pLit)

enum IdValueType
{
	Literal,
	Number,
	Bool
};

typedef std::variant<std::string, double, bool> LiteralValue;

inline IdValueType getValueActiveType(LiteralValue* value) {
	return (IdValueType)value->index();
}