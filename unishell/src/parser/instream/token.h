#pragma once

#include "../../utilities/stringUtil.h"

#include "../expression/type.h"

class Token;

typedef std::vector<Token> TokenList;

enum TokenEnum
{
	COMMAND, INDENTIFIER, 
	
	// sub tokens
	EXPRESSION,

	// math operators
	PLUS, MINUS, STAR, SLASH, LPAREN, RPAREN,

	// comparison operators
	BANG, LESS, GREATER,
	EQUAL_EQUAL, BANG_EQUAL, LESS_EQUAL, GREATER_EQUAL,
	AND, OR,

	// atribuition
	EQUAL,

	// data
	NUMBER, LITERAL, BOOLEANVAL
};

class Token
{
public:
	Token(TokenEnum type, const std::string& lexical, LiteralValue* lit, TokenList sub, size_t index) : 
		type(type), lexical(lexical), lit(lit), sub(sub), index(index)
	{}

	constexpr inline TokenEnum getType() const noexcept {
		return type;
	}

	inline std::string getLexical() const noexcept {
		return lexical;
	}

	inline LiteralValue* getLiteral() const noexcept {
		return lit;
	}

	constexpr inline size_t getIndex() const noexcept {
		return index;
	}

	inline TokenList getSub() const noexcept {
		return sub;
	}

private:
	TokenEnum type;
	std::string lexical;
	LiteralValue* lit;
	size_t index;

	TokenList sub;
};
