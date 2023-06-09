#pragma once

#include "../../algorithm/string/char.h"
#include "../../filesystem/handle/file.h"
#include "../../base/scanner_base.h"

#include "path_token.h"

class PathScanner : public ScannerBase<PathToken>
{
public:
	PathScanner(const std::string& src) : ScannerBase(src) {}

	PathTokenList scanTokens() override {
		while (!isAtEnd()) {
			start = current;
			scanToken();
		}

		return tokens;
	}

private:
	void scanToken() override;

	void addToken(const PathToken::Type type) noexcept {
		tokens.push_back(PathToken(type, getCurrentSubstring()));
	}

	// path to system root "C:/"
	void rootIdentifier() {
		if (src.size() >= 3 && fsys::File::exists(alg::string::charToStr(peekPrev()) + peek() + peekNext())) {
			current += 2;
			addToken(PathToken::Root);
		}
	}

	void identifier() noexcept {
		while (isValidChar(peek()) && !isAtEnd()) advance();
		if (peek() == ':' && !tokens.size()) rootIdentifier();
		else addToken(PathToken::IDENTIFIER);
	}

	static constexpr bool isValidChar(const char ch) noexcept {
		return (ch != '\\' && ch != '/' && ch != '*' && ch != '?' && 
				ch != '<' && ch != '>' && ch != '|' && ch != ':');
	}

	PathTokenList tokens;
};
