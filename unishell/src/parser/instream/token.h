#pragma once

#include "../../utilities/stringUtil.h"

class LiteralValue;

class Token;

typedef std::vector<Token> TokenList;

enum TokenEnum
{
	// word tokens
	COMMAND, RETCOMMAND, INRETCOMMAND, IDENTIFIER, FLAG,
	
	// sub tokens
	EXPRESSION, COLOR, LIST, OBJECT,

	// math operators
	PLUS, MINUS, STAR, SLASH, LPAREN, RPAREN,

	// comparison operators
	BANG, LESS, GREATER,
	EQUAL_EQUAL, EQUAL_EQUAL_EQUAL, BANG_EQUAL, LESS_EQUAL, GREATER_EQUAL,
	
	// keywords
	AND, OR, NULLVAL,

	// others
	COLON, LBRACE, RBRACE, LBRACKET, RBRACKET,

	// atribuition
	EQUAL,

	// data
	NUMBER, LITERAL, BOOLEANVAL
};

class Token
{
public:
	friend class TokenProcess;

	Token(TokenEnum type, const std::string& lexical, LiteralValue* lit, const TokenList& sub, size_t index) : 
		type(type), lexical(lexical), lit(lit), sub(sub), index(index)
	{}

	constexpr inline TokenEnum getType() const noexcept {
		return type;
	}

	inline std::string getLexical() const noexcept {
		return lexical;
	}

	constexpr inline LiteralValue* getLiteral() const noexcept {
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
