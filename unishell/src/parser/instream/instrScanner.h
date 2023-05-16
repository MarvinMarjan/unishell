#pragma once

#include "../../system/system.h"

#include "../../utilities/stringUtil.h"
#include "../../utilities/typeUtil.h"

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

	TokenList scanTokens() override;

private:
	void scanToken() override;

	// indentify expressions and generate a EXPRESSION type conataining
	// the expression body
	static TokenList generateExpressions(TokenList source) {
		TokenList res;

		size_t start = 0;
		size_t end = 0;

		unsigned short aux = 0;

		for (size_t i = 0; i < source.size(); i++)
		{
			if (source[i].getType() == LPAREN) {
				aux++;

				start = i;

				while (aux) {
					i++;

					if (source[i].getType() == LPAREN) aux++;
					if (source[i].getType() == RPAREN) aux--;
				}

				end = i;

				res.push_back(Token(EXPRESSION, "", nullptr, TokenList(source.begin() + start + 1, source.begin() + end)));
			}

			else res.push_back(source[i]);
		}

		return res;
	}


	inline void addToken(TokenEnum type) noexcept {
		tokens.push_back(Token(type, getCurrentSubstring(), nullptr, {}));
	}

	inline void addToken(TokenEnum type, const std::string& lex) noexcept {
		tokens.push_back(Token(type, lex, nullptr, {}));
	}

	inline void addToken(TokenEnum type, LiteralValue* lit) noexcept {
		tokens.push_back(Token(type, getCurrentSubstring(), lit, {}));
	}

	inline void addExpression(TokenList exprBody) noexcept {
		tokens.push_back(Token(EXPRESSION, "", nullptr, exprBody));
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