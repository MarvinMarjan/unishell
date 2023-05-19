#pragma once

#include "../utilities/fileUtil.h"
#include "../utilities/stringUtil.h"

#include "../base/scannerBase.h"

#include "pathToken.h"

class PathScanner : public ScannerBase<PathToken>
{
public:
	PathScanner(const std::string& src) : ScannerBase(src) {}

	inline PathTokenList scanTokens() override {
		while (!isAtEnd()) {
			start = current;
			scanToken();
		}

		return tokens;
	}

private:
	void scanToken() override;

	inline void addToken(PathToken::PathTokenType type) noexcept {
		tokens.push_back(PathToken(type, getCurrentSubstring()));
	}

	// path to system root "C:/"
	inline void rootIdentifier() {
		if (src.size() >= 3 && FileUtil::exists(StringUtil::charToStr(peekPrev()) + peek() + peekNext())) {
			current += 2;
			addToken(PathToken::Root);
		}
	}

	inline void indentifier() noexcept {
		while (isValidChar(peek()) && !isAtEnd()) advance();
		if (peek() == ':' && !tokens.size()) rootIdentifier();
		else addToken(PathToken::INDENTIFIER);
	}

	static constexpr inline bool isValidChar(char ch) noexcept {
		return (ch != '\\' && ch != '/' && ch != '*' && ch != '?' && 
				ch != '<' && ch != '>' && ch != '|' && ch != ':');
	}

	PathTokenList tokens;
};
