#pragma once

#include "../../utilities/stringUtil.h"

class InputToken;

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
