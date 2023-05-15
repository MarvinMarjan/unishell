#pragma once

#include "../../utilities/stringUtil.h"

#include "type.h"

class ExprToken;

typedef std::vector<ExprToken> ExprTokenList;

enum ExprTokenType
{
	// math operators
	PLUS, MINUS, STAR, SLASH, LPAREN, RPAREN,
	
	// comparison operators
	BANG, LESS, GREATER,
	EQUAL_EQUAL, BANG_EQUAL, LESS_EQUAL, GREATER_EQUAL,
	AND, OR,

	// literals
	NUMBER
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
