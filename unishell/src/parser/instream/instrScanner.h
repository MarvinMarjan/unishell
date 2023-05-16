#pragma once

#include "../../system/systemException.h"

#include "../../utilities/stringUtil.h"

#include "../../base/scannerBase.h"
#include "token.h"

class InputScanner : public ScannerBase<InputToken>
{
public:
	InputScanner(const std::string& src) : ScannerBase(src) {}

	InputTokenList scanTokens() override {
		while (!isAtEnd()) {
			start = current;
			scanToken();
		}

		return tokens;
	}

private:
	void scanToken() override;

	inline void addToken(InputTokenType type) noexcept {
		tokens.push_back(InputToken(type, getCurrentSubstring()));
	}

	inline void addToken(InputTokenType type, const std::string& lex) noexcept {
		tokens.push_back(InputToken(type, lex));
	}

	inline void string() noexcept {
		while (peek() != '\"' && !isAtEnd()) advance();

		addToken(Literal, src.substr(start + 1, current - 1 - start));

		advance(); // closing char
	}

	void expression(); // an expression is between '(' and ')'

	inline void word(InputTokenType type) {
		while (StringUtil::isAlphaNumeric(peek())) advance();
		addToken(type);
	}

	InputTokenList tokens;
};