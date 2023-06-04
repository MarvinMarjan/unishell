#pragma once

#include "../instream/token.h"
#include "../../utilities/stringUtil.h"

#include "../../system/systemException.h"

#include <variant>
#include <map>

#define asStr(pLit)  std::get<std::string>(*pLit)
#define asDbl(pLit)  std::get<double>(*pLit)
#define asBool(pLit)  std::get<bool>(*pLit)
#define asList(pLit)  std::get<std::vector<LiteralValue*>>(*pLit)
#define asObj(pLit)  std::get<std::map<std::string, LiteralValue*>>(*pLit)


enum IdValueType
{
	Literal,
	Number,
	Bool,
	List,
	Object,
	
	Null,
	Any
};

typedef std::vector<IdValueType> IdValueTypeList;

class LiteralValue;

typedef std::vector<LiteralValue*> LiteralValueList;
typedef std::map<std::string, LiteralValue*> LiteralValueObj;

typedef std::variant<std::string, double, bool, LiteralValueList, LiteralValueObj> LiteralValuePtr;

constexpr inline IdValueType getValueType(LiteralValue* value) noexcept;

class LiteralValue : public LiteralValuePtr
{
public:
	LiteralValue(LiteralValuePtr other) : LiteralValuePtr(other) {}

	inline IdValueType type() const noexcept {
		return getValueType((LiteralValue*)this);
	}
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

inline LiteralValue* litList(LiteralValueList value) noexcept {
	return new LiteralValue(value);
}

inline LiteralValue* litObj(LiteralValueObj value) noexcept {
	return new LiteralValue(value);
}


constexpr inline IdValueType getValueType(LiteralValue* value) noexcept {
	if (!value) return Null;
	return (IdValueType)value->index();
}

inline LiteralValue* getListFromTokenList(TokenList source) {
	LiteralValue* lit = new LiteralValue(LiteralValueList());

	for (Token token : source)
		asList(lit).push_back(token.getLiteral());

	return lit;
}

inline LiteralValue* getObjFromTokenList(TokenList source) {
	LiteralValue* lit = new LiteralValue(std::map<std::string, LiteralValue*>());
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