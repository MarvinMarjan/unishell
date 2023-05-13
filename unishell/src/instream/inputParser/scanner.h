#pragma once

#include "../../utilities/stringUtil.h"

#include "token.h"

class InputScanner
{
public:
	InputScanner(const std::string& src);

	inline InputTokenList scanTokens() {
		while (!isAtEnd()) {
			start = current;
			scanToken();
		}

		return tokens;
	}

private:
	void scanToken();

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

	inline bool isAtEnd() const noexcept {
		return current >= src.size();
	}

	inline bool match(char ch) noexcept {
		if (isAtEnd() || peek() != ch) return false;

		current++;
		return true;
	}

	inline char advance() noexcept {
		return src[current++];
	}

	inline char peek() noexcept {
		return src[current];
	}

	inline char peekNext() const noexcept {
		if (current + 1 >= src.size()) return '\0';
		return src[current + 1];
	}

	InputTokenList tokens;

	std::string src;

	size_t start;
	size_t current;
};