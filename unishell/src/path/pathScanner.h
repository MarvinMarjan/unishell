#pragma once

#include "../utilities/fileUtil.h"
#include "../utilities/stringUtil.h"

#include "pathToken.h"

class PathScanner
{
public:
	PathScanner(const std::string& src);

	inline TokenList scanTokens() noexcept {
		while (!isAtEnd()) {
			start = current;
			scanToken();
		}

		return tokens;
	}

private:
	inline void addToken(PathTokenType type) noexcept {
		tokens.push_back(PathToken(type, src.substr(start, current - start)));
	}

	void scanToken();

	// path to system root "C:/"
	inline void rootIndentifier() {
		if (src.size() >= 3 && FileUtil::exists(UTCharToStr(peekPrev()) + peek() + peekNext())) {
			current += 2;
			addToken(Root);
		}

		// TODO: else, throw a error
	}

	inline void indentifier() noexcept {
		while (isValidChar(peek()) && !isAtEnd()) advance();
		if (peek() == ':' && !tokens.size()) rootIndentifier();
		else addToken(Indentifier);
	}

	inline bool isAtEnd() const noexcept {
		return current >= src.size();
	}

	inline bool match(char ch) noexcept {
		if (isAtEnd()) return false;
		if (peek() != ch) return false;

		current++;
		return true;
	}

	inline char advance() noexcept {
		return src[current++];
	}

	inline char peek() const noexcept {
		return src[current];
	}
	
	inline char peekNext() const noexcept {
		if ((size_t)current + 1 >= src.size()) return '\0';
		return src[(size_t)current + 1];
	}

	inline char peekPrev() const noexcept {
		if ((size_t)current - 1 < 0) return '\0';
		return src[(size_t)current - 1];
	}

	static constexpr inline bool isValidChar(char ch) noexcept {
		return (ch != '\\' && ch != '/' && ch != '*' && ch != '?' && 
				ch != '<' && ch != '>' && ch != '|' && ch != ':');
	}

	TokenList tokens;

	std::string src;

	unsigned int start;
	unsigned int current;
};
