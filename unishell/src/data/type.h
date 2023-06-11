#pragma once

#include "../instream/scanner/token.h"

#include "../system/exception/systemException.h"

#include <variant>
#include <map>

#define asStr(pLit)		std::get<std::string>(*pLit)
#define asDbl(pLit)		std::get<double>(*pLit)
#define asBool(pLit)	std::get<bool>(*pLit)
#define asList(pLit)	std::get<std::vector<LiteralValue*>>(*pLit)
#define asObj(pLit)		std::get<std::map<std::string, LiteralValue*>>(*pLit)


enum LiteralValueType
{
	Literal,
	Number,
	Bool,
	List,
	Object,
	
	Null,
	Any
};

typedef std::vector<LiteralValueType> LiteralValueTypeList;

class LiteralValue;

typedef std::vector<LiteralValue*> LiteralValueList;
typedef LiteralValueList LitList;

typedef std::map<std::string, LiteralValue*> LiteralValueObject;
typedef LiteralValueObject LitObj;

typedef std::variant<std::string, double, bool, LitList, LitObj> LiteralValuePtr;

constexpr inline LiteralValueType getValueType(LiteralValue* value) noexcept;

class LiteralValue : public LiteralValuePtr
{
public:
	LiteralValue(LiteralValuePtr other) : LiteralValuePtr(other) {}

	constexpr inline LiteralValueType type() const noexcept {
		return getValueType((LiteralValue*)this);
	}
};

template <typename T>
constexpr inline LiteralValue* lit(const T& value) noexcept {
	return new LiteralValue(LiteralValuePtr(value));
}

constexpr inline LiteralValue* lit(const int value) noexcept {
	return new LiteralValue(LiteralValuePtr((double)value));
}



constexpr inline LiteralValueType getValueType(LiteralValue* value) noexcept {
	if (!value) return Null;
	return (LiteralValueType)value->index();
}

inline LiteralValue* getListFromTokenList(const TokenList& source) {
	LiteralValue* const lit = new LiteralValue(LitList());

	for (const Token& token : source)
		asList(lit).push_back(token.getLiteral());

	return lit;
}

inline LiteralValue* getObjFromTokenList(TokenList source) {
	LiteralValue* const lit = new LiteralValue(std::map<std::string, LiteralValue*>());
	LiteralValue* aux;

	for (Token token : source) {
		if (token.getType() != LIST) continue;
		if (!token.getLiteral()) continue;
		if (asList(token.getLiteral()).size() < 2) continue;

		aux = token.getLiteral();

		if (getValueType(asList(aux)[0]) != Literal)
			throw SystemException(TokenProcessingError, "Literal type expected for property name", ExceptionRef(*__userInput, token.getIndex()));

		asObj(lit).insert({ asStr(asList(aux)[0]), asList(aux)[1] });
	}

	return lit;
}