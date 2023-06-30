#pragma once

#include <string>
#include <vector>

namespace lit
{
	class LiteralValue;
}

class Token;


using TokenList = std::vector<Token>;


enum TokenEnum
{
	// word tokens
	RETCOMMAND, INRETCOMMAND, IDENTIFIER, FLAG,
	
	// sub tokens
	BLOCK, EXPRESSION, COLOR, LIST, OBJECT,

	// math operators
	PLUS, MINUS, STAR, SLASH, LPAREN, RPAREN,

	// comparison operators
	BANG, LESS, GREATER,
	EQUAL_EQUAL, EQUAL_EQUAL_EQUAL, BANG_EQUAL, LESS_EQUAL, GREATER_EQUAL,
	
	// keywords
	AND, OR, NULLVAL, UNPACK, BEGIN, END,

	// others
	COLON, LBRACE, RBRACE, LBRACKET, RBRACKET,

	// atribuition
	EQUAL,

	// data
	NUMBER, LITERAL, BOOLEANVAL,

	// analisys
	ENDLINE
};

class Token
{
public:
	friend class TokenProcess;

	Token(const TokenEnum type, const std::string& lexical, lit::LiteralValue* lit, const TokenList& sub, const size_t index, const size_t line = 1) : 
		type(type), lexical(lexical), lit(lit), sub(sub), index(index), line(line)
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

	constexpr size_t getLine() const noexcept {
		return line;
	}

	TokenList getSub() const noexcept {
		return sub;
	}

private:
	TokenEnum type;
	std::string lexical;
	lit::LiteralValue* lit;
	size_t index;
	size_t line;

	TokenList sub;
};

constexpr inline TokenEnum keywordToTokenEnum(const std::string& keyword) noexcept {
	if (keyword == "and") return AND;
	if (keyword == "or") return OR;
	if (keyword == "null") return NULLVAL;
	if (keyword == "unpack") return UNPACK;
	if (keyword == "begin") return BEGIN;
	if (keyword == "end") return END;

	return LITERAL;
}