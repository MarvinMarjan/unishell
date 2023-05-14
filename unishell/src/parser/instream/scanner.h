#pragma once

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

	inline void addToken(InputToken::InputTokenType type) noexcept {
		tokens.push_back(InputToken(type, src.substr(start, current - start)));
	}

	inline void addToken(InputToken::InputTokenType type, const std::string& lex) noexcept {
		tokens.push_back(InputToken(type, lex));
	}

	inline void string() noexcept {
		while (peek() != '\"' && !isAtEnd()) advance();

		addToken(InputToken::Literal, src.substr(start + 1, current - 1 - start));

		advance(); // closing char
	}

	inline void expression() noexcept {
		unsigned short aux = 0;

		while (!isAtEnd()) {
			if (peek() == '(') aux++;
			if (peek() == ')' && aux) aux--;

			else if (peek() == ')' && !aux) break;

			advance();
		}

		addToken(InputToken::Expression, src.substr(start + 1, current - 1 - start));
		
		advance(); // closing char
	}

	inline void characters(InputToken::InputTokenType type) {
		while (StringUtil::isAlphaNumeric(peek())) advance();
		addToken(type);
	}

	InputTokenList tokens;
};