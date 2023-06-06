#pragma once

#include "../../system/system.h"

#include "../../utilities/stringUtil.h"
#include "../../utilities/typeUtil.h"

#include "../../base/scannerBase.h"
#include "token.h"

#include "../../system/global.h"
#include "../../utilities/globalUtil.h"

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
		TokenEnum keyw = GlobalUtil::keywordToToken(keyword);
		if (keyw != LITERAL) {
			addToken(keyw);
			return true;
		}

		return false;
	}


	// gets a string inside quotes like "hello, world"
	inline void string(char delimiter, bool raw = false) {
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

	constexpr inline char checkEscapeChar(char ch) const noexcept {
		switch (ch)
		{
		case 'n':  return '\n';
		case 't':  return '\t';
		case '\\': return '\\';
		case '\"': return '\"';
		}

		return '\0';
	}

	inline void addEscapeChar() {
		char aux;

		if ((aux = checkEscapeChar(peek())) == '\0')
			throw SystemException(InstreamScannerError, "Unknown escape character", ExceptionRef(USER_INPUT, current));

		src.erase(src.begin() + current);
		src[current - 1] = aux;
	}

	// gets a sequence of digits. dot ('.') included
	inline void number() {
		for (current; StringUtil::isDigit(peek()); current++) {}
		addToken(NUMBER, new LiteralValue(std::stod(getCurrentSubstring())));
	}

	// if is keyword, returns true and add it
	// else return false
	inline bool keyword() {
		for (current; StringUtil::isAlpha(peek()); current++) {}
		return addKeyword(getCurrentSubstring());
	}

	// if is boolean value, returns true and add it;
	// else return false
	inline bool boolean() {
		for (current; StringUtil::isAlpha(peek()); current++) {}
		return addBoolean(getCurrentSubstring());
	}

	// gets a sequence of alpha / digits characters
	inline void word(TokenEnum type, bool hasLiteral = false) {
		while (StringUtil::isAlphaNumeric(peek())) advance();
		if (!hasLiteral) addToken(type, getCurrentSubstring());
		else addToken(type, new LiteralValue(getCurrentSubstring()));
	}

	TokenList tokens;

	bool ignoreCommand;
};