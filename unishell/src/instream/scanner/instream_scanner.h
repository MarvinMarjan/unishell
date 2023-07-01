#pragma once

#include "../../system/system.h"
#include "../../algorithm/string/char.h"
#include "../../algorithm/bit/operations.h"
#include "../../base/scanner_base.h"
#include "../../data/litvalue/checking.h"
#include "../../data/litvalue/litformat.h"
#include "instream_token.h"

enum InstreamScannerHints {
	IgnoreCommand = 0x01,
	AddEndlTokens = 0x02
};

class InstreamScanner : public ScannerBase<Token>
{
public:
	InstreamScanner(const std::string& src, const int hints = 0)
		: ScannerBase(src), hints(hints)
	{
		ignoreCommand = alg::bit::hasBits(hints, IgnoreCommand);
		addEndlTokens = alg::bit::hasBits(hints, AddEndlTokens);

		currentLine = 1;
		nestLevel = 0;
	}

	TokenList scanTokens() override;

	static std::vector<TokenList> separateLinesFromTokens(TokenList tokens);

private:
	void scanToken() override;


	void addToken(const TokenEnum type, bool ignoreByLineSplitter = false) noexcept {
		tokens.push_back(Token(type, getCurrentSubstring(), nullptr, {}, current - 1, currentLine, ignoreByLineSplitter));
	}

	void addToken(const TokenEnum type, const std::string& lex) noexcept {
		tokens.push_back(Token(type, lex, nullptr, {}, current - 1, currentLine));
	}

	void addToken(const TokenEnum type, lit::LiteralValue* lit) noexcept {
		tokens.push_back(Token(type, getCurrentSubstring(), lit, {}, current - 1, currentLine));
	}

	bool addBoolean(const std::string& boolStr) {
		if (lit::isBoolean(boolStr)) {
			addToken(BOOLEANVAL, new lit::LiteralValue(lit::stringToBool(boolStr)));
			return true;
		}

		return false;
	}

	bool addKeyword(const std::string& keyword) {
		const TokenEnum keyw = keywordToTokenEnum(keyword);

		if (keyw != LITERAL) {
			addToken(keyw);
			return true;
		}

		return false;
	}


	// gets a string inside quotes like "hello, world"
	void string(const char delimiter, const bool raw = false);

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
			throw new InstreamScannerErr("Unknown escape character", ExceptionRef(UNISHLL_USER_INPUT, current));

		src.erase(src.begin() + current);
		src[current - 1] = aux;
	}

	// gets a sequence of digits. dot ('.') included
	void number() {
		for (current; alg::string::isDigit(peek()); current++) {}
		addToken(NUMBER, new lit::LiteralValue(std::stod(getCurrentSubstring())));
	}
	
	// if is keyword, returns true and add it;
	// else return false
	bool keyword() {
		return addKeyword(advanceWord());
	}

	// if is boolean value, returns true and add it;
	// else return false
	bool boolean() {
		return addBoolean(advanceWord());
	}


	bool block();


	// gets a sequence of alpha / digits characters
	void word(const TokenEnum type, const bool hasLiteral = false) {
		while (alg::string::isAlphaNumeric(peek())) advance();
		if (!hasLiteral) addToken(type, getCurrentSubstring());
		else addToken(type, new lit::LiteralValue(getCurrentSubstring()));
	}

	TokenList tokens;

	bool ignoreCommand;
	bool addEndlTokens;

	int nestLevel;

	const int hints;

	size_t currentLine;
};