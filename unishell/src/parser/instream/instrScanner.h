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

	// indentify expressions and generate a EXPRESSION type conataining
	// the expression body
	TokenList generateExpressions(TokenList source);

	inline void checkIndex(TokenList source, size_t& i, unsigned short aux) {
		if (i + 1 >= source.size() && aux)
			throw SystemException(InstreamScannerError, "Unterminated expression", ExceptionRef(src, source[i].getIndex()));

		else
			i++;
	}

	inline void checkParen(TokenList source, size_t& i, unsigned short& aux) {
		if (source[i].getType() == LPAREN) aux++;
		if (source[i].getType() == RPAREN) aux--;
	}



	inline TokenList reviewTokens(TokenList source) {
		TokenList res;

		for (Token token : source) {
			if (token.type == INDENTIFIER)
				token = assignIdentifierToken(token);

			res.push_back(token);
		}

		return res;
	}

	// receive a token that represents a symbol and return a new token
	// containing the value inside that symbol
	static inline Token assignIdentifierToken(Token token) {
		Identifier respectiveId = *System::getEnvId(token.lexical.substr(1), (int)token.index);
		LiteralValue idValue = respectiveId.getValue();

		token.lexical = TypeUtil::literalValueToString(&idValue);
		token.lit = new LiteralValue(idValue);
		token.type = respectiveId.getTypeAsTokenEnum();

		return token;
	}



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