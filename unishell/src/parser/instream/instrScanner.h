#pragma once

#include "../../system/system.h"

#include "../../utilities/stringUtil.h"
#include "../../utilities/typeUtil.h"

#include "../../base/scannerBase.h"
#include "token.h"

enum InstreamScannerHints
{
	IgnoreCommand = 1
};

class InstreamScanner : public ScannerBase<Token>
{
public:
	InstreamScanner(const std::string& src, int hints = 0) : ScannerBase(src) {
		ignoreCommand = ((hints & IgnoreCommand) == IgnoreCommand);
	}

	TokenList scanTokens() override;

private:
	void scanToken() override;


	inline void addToken(TokenEnum type) noexcept {
		tokens.push_back(Token(type, getCurrentSubstring(), nullptr, {}, current - 1));
	}

	inline void addToken(TokenEnum type, const std::string& lex) noexcept {
		tokens.push_back(Token(type, lex, nullptr, {}, current - 1));
	}

	inline void addToken(TokenEnum type, LiteralValue* lit) noexcept {
		tokens.push_back(Token(type, getCurrentSubstring(), lit, {}, current - 1));
	}

	inline bool addBoolean(const std::string& boolStr) {
		if (TypeUtil::isBoolean(boolStr)) {
			addToken(BOOLEANVAL, new LiteralValue(TypeUtil::stringToBool(boolStr)));
			return true;
		}

		return false;
	}

	inline bool addKeyword(const std::string& keyword) {
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



	inline void string() noexcept {
		while (peek() != '\"' && !isAtEnd()) advance();
		addToken(LITERAL, new LiteralValue(src.substr(start + 1, current - 1 - start)));
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

	inline bool boolean() {
		for (current; StringUtil::isAlpha(peek()); current++) {}
		return addBoolean(getCurrentSubstring());
	}

	inline void word(TokenEnum type, bool hasLiteral = false) {
		while (StringUtil::isAlphaNumeric(peek())) advance();
		if (!hasLiteral) addToken(type, getCurrentSubstring());
		else addToken(type, new LiteralValue(getCurrentSubstring()));
	}

	TokenList tokens;

	bool ignoreCommand;
};