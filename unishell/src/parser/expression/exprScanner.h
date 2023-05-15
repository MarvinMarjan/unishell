#pragma once

#include "../../base/scannerBase.h"

#include "token.h"

class ExprScanner : ScannerBase<ExprToken>
{
public:
	ExprScanner(const std::string& src) : ScannerBase(src) {}

	ExprTokenList scanTokens() override;

private:
	void scanToken() override;

	inline void addToken(ExprTokenType type) {
		tokens.push_back(ExprToken(type, getCurrentSubstring(), nullptr));
	}

	inline void addToken(ExprTokenType type, LiteralValue* lit) {
		tokens.push_back(ExprToken(type, getCurrentSubstring(), lit));
	}

	inline void number() {
		for (current; StringUtil::isDigit(peek()); current++) {}
		addToken(NUMBER, new LiteralValue(std::stod(getCurrentSubstring())));
	}

	inline bool keyword() {
		for (current; StringUtil::isAlpha(peek()); current++) {}
		return addKeyword(getCurrentSubstring());
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

	ExprTokenList tokens;
};
