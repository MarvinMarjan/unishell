#pragma once

#include "../../system/system.h"

#include "../../utilities/stringUtil.h"

#include "../../base/scannerBase.h"
#include "token.h"

enum InputScannerHints
{
	IgnoreCommand = 1
};

class InputScanner : public ScannerBase<Token>
{
public:
	InputScanner(const std::string& src, int hints = 0) : ScannerBase(src) {
		ignoreCommand = ((hints & IgnoreCommand) == IgnoreCommand);
	}

	TokenList scanTokens() override {
		while (!isAtEnd()) {
			start = current;
			scanToken();
		}

		return tokens;
	}

private:
	void scanToken() override;

	inline void addToken(TokenEnum type) noexcept {
		tokens.push_back(Token(type, getCurrentSubstring(), nullptr));
	}

	inline void addToken(TokenEnum type, const std::string& lex) noexcept {
		tokens.push_back(Token(type, lex, nullptr));
	}

	inline void addToken(TokenEnum type, LiteralValue* lit) {
		tokens.push_back(Token(type, getCurrentSubstring(), lit));
	}

	inline void string() noexcept {
		while (peek() != '\"' && !isAtEnd()) advance();

		addToken(LITERAL, src.substr(start + 1, current - 1 - start));

		advance(); // closing char
	}

	inline void number() {
		for (current; StringUtil::isDigit(peek()); current++) {}
		addToken(NUMBER, new LiteralValue(std::stod(getCurrentSubstring())));
	}

	inline bool keyword() {
		for (current; StringUtil::isAlpha(peek()); current++) {}
		return addKeyword(getCurrentSubstring());
	}

	inline void word(TokenEnum type) {
		while (StringUtil::isAlphaNumeric(peek())) advance();
		addToken(type);
	}

	inline bool addKeyword(const std::string keyword) {
		if (keyword == "and") {
			addToken(AND);
			return true;
		}

		else if (keyword == "or") {
			addToken(OR);
			return true;
		}

		return false;
	}

	void expression(); // an expression is between '(' and ')'

	TokenList tokens;

	bool ignoreCommand;
};