#pragma once

#include "../utilities/stringUtil.h"

template <typename T>
class ScannerBase 
{
public:
	ScannerBase(const std::string& src) : src(src) {
		current = 0;
		start = 0;
	}

	virtual std::vector<T> scanTokens() = 0;

protected:
	virtual void scanToken() = 0;

	virtual std::string getCurrentSubstring() const noexcept {
		return src.substr(start, current - start);
	}

	virtual bool isAtEnd() const noexcept {
		return current >= src.size();
	}

	virtual bool match(const char ch) noexcept {
		if (isAtEnd() || peek() != ch) return false;

		current++;
		return true;
	}

	virtual char advance() noexcept {
		return src[current++];
	}

	virtual char peek() const noexcept {
		return src[current];
	}

	virtual char peekNext() const noexcept {
		if (current + 1 >= src.size()) return '\0';
		return src[current + 1];
	}

	virtual char peekPrev() const noexcept {
		if (current - 1 < 0) return '\0';
		return src[current - 1];
	}

	std::string src;

	size_t start;
	size_t current;
};
