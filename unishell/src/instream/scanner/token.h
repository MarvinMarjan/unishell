#pragma once

#include <string>
#include <vector>

namespace lit
{
	class LiteralValue;
}

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

	Token(const TokenEnum type, const std::string& lexical, lit::LiteralValue* lit, const TokenList& sub, const size_t index) : 
		type(type), lexical(lexical), lit(lit), sub(sub), index(index)
	{}

	constexpr TokenEnum getType() const noexcept {
		return type;
	}

	constexpr std::string getLexical() const noexcept {
		return lexical;
	}

	constexpr lit::LiteralValue* getLiteral() const noexcept {
		return lit;
	}

	constexpr size_t getIndex() const noexcept {
		return index;
	}

	TokenList getSub() const noexcept {
		return sub;
	}

private:
	TokenEnum type;
	std::string lexical;
	lit::LiteralValue* lit;
	size_t index;

	TokenList sub;
};

constexpr inline TokenEnum keywordToTokenEnum(const std::string& keyword) noexcept {
	if (keyword == "and") return AND;
	if (keyword == "or") return OR;
	if (keyword == "null") return NULLVAL;

	return LITERAL;
}