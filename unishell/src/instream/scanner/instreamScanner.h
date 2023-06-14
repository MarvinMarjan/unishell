#pragma once

#include "../../system/system.h"

#include "../../utilities/stringUtil.h"
#include "../../utilities/typeUtil.h"

#include "../../base/scannerBase.h"
#include "token.h"

#include "../../system/global/global.h"
#include "../../utilities/globalUtil.h"

enum InstreamScannerHints {
	IgnoreCommand = 1
};

class InstreamScanner : public ScannerBase<Token>
{
public:
	InstreamScanner(const std::string& src, const int hints = 0) : ScannerBase(src) {
		ignoreCommand = OPUtil::bwAnd(hints, IgnoreCommand);
	}

	TokenList scanTokens() override;

private:
	void scanToken() override;


	void addToken(const TokenEnum type) noexcept {
		tokens.push_back(Token(type, getCurrentSubstring(), nullptr, {}, current - 1));
	}

	void addToken(const TokenEnum type, const std::string& lex) noexcept {
		tokens.push_back(Token(type, lex, nullptr, {}, current - 1));
	}

	void addToken(const TokenEnum type, LiteralValue* lit) noexcept {
		tokens.push_back(Token(type, getCurrentSubstring(), lit, {}, current - 1));
	}

	bool addBoolean(const std::string& boolStr) {
		if (TypeUtil::isBoolean(boolStr)) {
			addToken(BOOLEANVAL, new LiteralValue(TypeUtil::stringToBool(boolStr)));
			return true;
		}

		return false;
	}

	bool addKeyword(const std::string& keyword) {
		TokenEnum keyw = GlobalUtil::keywordToToken(keyword);
		if (keyw != LITERAL) {
			addToken(keyw);
			return true;
		}

		return false;
	}


	// gets a string inside quotes like "hello, world"
	void string(const char delimiter, const bool raw = false) {
		while (peek() != delimiter) {
			if (isAtEnd()) 
				throw SystemException(InstreamScannerError, "Unterminated string", ExceptionRef(USER_INPUT, current - 1));

			if (advance() != '\\' || raw) continue;

			// escape character processing
			addEscapeChar();
		}

		addToken(LITERAL, new LiteralValue(src.substr(start + 1, current - 1 - start)));
		advance(); // closing char
	}

	constexpr char checkEscapeChar(const char ch) const noexcept {
		switch (ch)
		{
		case 'n':  return '\n';
		case 't':  return '\t';
		case '\\': return '\\';
		case '\"': return '\"';
		}

		return '\0';
	}

	void addEscapeChar() {
		char aux;

		if ((aux = checkEscapeChar(peek())) == '\0')
			throw SystemException(InstreamScannerError, "Unknown escape character", ExceptionRef(USER_INPUT, current));

		src.erase(src.begin() + current);
		src[current - 1] = aux;
	}

	// gets a sequence of digits. dot ('.') included
	void number() {
		for (current; StringUtil::isDigit(peek()); current++) {}
		addToken(NUMBER, new LiteralValue(std::stod(getCurrentSubstring())));
	}
	
	// if is keyword, returns true and add it
	// else return false
	bool keyword() {
		for (current; StringUtil::isAlpha(peek()); current++) {}
		return addKeyword(getCurrentSubstring());
	}

	// if is boolean value, returns true and add it;
	// else return false
	bool boolean() {
		for (current; StringUtil::isAlpha(peek()); current++) {}
		return addBoolean(getCurrentSubstring());
	}

	// gets a sequence of alpha / digits characters
	void word(const TokenEnum type, const bool hasLiteral = false) {
		while (StringUtil::isAlphaNumeric(peek())) advance();
		if (!hasLiteral) addToken(type, getCurrentSubstring());
		else addToken(type, new LiteralValue(getCurrentSubstring()));
	}

	TokenList tokens;

	bool ignoreCommand;
};