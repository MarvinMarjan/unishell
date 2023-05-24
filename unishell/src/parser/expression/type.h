#pragma once

#include "../instream/token.h"
#include "../../utilities/stringUtil.h"
#include <variant>

#define asStr(pLit)  std::get<std::string>(*pLit)
#define asDbl(pLit)  std::get<double>(*pLit)
#define asBool(pLit) std::get<bool>(*pLit)
#define asList(pLit) std::get<std::vector<LiteralValue*>>(*pLit)

enum IdValueType
{
	Literal,
	Number,
	Bool,
	List,
	Null
};

class LiteralValue;

typedef std::variant<std::string, double, bool, std::vector<LiteralValue*>> LiteralValuePtr;

class LiteralValue : public LiteralValuePtr
{
public:
	LiteralValue(LiteralValuePtr other) : LiteralValuePtr(other) {}
};


inline LiteralValue* litStr(const std::string& value) noexcept {
	return new LiteralValue(value);
}

inline LiteralValue* litNum(double value) noexcept {
	return new LiteralValue(value);
}

inline LiteralValue* litBool(bool value) noexcept {
	return new LiteralValue(value);
}

inline LiteralValue* litList(std::vector<LiteralValue*> value) noexcept {
	return new LiteralValue(value);
}



inline IdValueType getValueType(LiteralValue* value) {
	if (!value) return Null;
	return (IdValueType)value->index();
}

inline LiteralValue* getFromTokenList(TokenList source) {
	LiteralValue* lit = new LiteralValue(std::vector<LiteralValue*>());

	for (Token token : source)
		asList(lit).push_back(token.getLiteral());

	return lit;
}