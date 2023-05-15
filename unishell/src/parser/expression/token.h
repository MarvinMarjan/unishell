#pragma once

#include "../../utilities/stringUtil.h"

#include "type.h"

class ExprToken;

typedef std::vector<ExprToken> ExprTokenList;

enum ExprTokenType
{
	PLUS, MINUS, STAR, SLASH, BANG, LESS, GREATER,
	EQUAL_EQUAL, BANG_EQUAL, LESS_EQUAL, GREATER_EQUAL,
	NUMBER, LPAREN, RPAREN
};

class ExprToken
{
public:
	ExprToken(ExprTokenType type, const std::string& lexical, LiteralValue* lit) : type(type), lexical(lexical), lit(lit) {}

	constexpr inline ExprTokenType getType() const noexcept {
		return type;
	}

	inline std::string getLexical() const noexcept {
		return lexical;
	}

	inline LiteralValue* getLiteral() const noexcept {
		return lit;
	}

private:
	ExprTokenType type;
	std::string lexical;
	LiteralValue* lit;
};
