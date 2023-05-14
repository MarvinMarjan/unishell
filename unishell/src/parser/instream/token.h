#pragma once

#include "../../utilities/stringUtil.h"

#include "../expression/type.h"

class InputToken;
class ExprToken;

typedef std::vector<InputToken> InputTokenList;

class InputToken
{
public:
	enum InputTokenType
	{
		Command, Literal, Indentifier, Expression
	};

	InputToken(InputTokenType type, const std::string& lexical) : type(type), lexical(lexical) {}

	constexpr inline InputTokenType getType() const noexcept {
		return type;
	}

	inline std::string getLexical() const noexcept {
		return lexical;
	}

private:
	InputTokenType type;
	std::string lexical;
};

class ExprToken
{
public:
	enum ExprTokenType
	{
		PLUS, MINUS, STAR, SLASH,
		NUMBER, LPAREN, RPAREN
	};

	ExprToken(ExprTokenType type, const std::string& lexical) : type(type), lexical(lexical) {}

	constexpr inline ExprTokenType getType() const noexcept {
		return type;
	}

	inline std::string getLexical() const noexcept {
		return lexical;
	}

private:
	ExprTokenType type;
	std::string lexical;
};
