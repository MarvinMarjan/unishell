#pragma once

#include "../utilities/stringUtil.h"

#include "../system/systemException.h"

template <typename T>
class ScannerBase 
{
public:
	inline constexpr ScannerBase(const std::string& src) : src(src) {
		current = 0;
		start = 0;
	}

	virtual std::vector<T> scanTokens() = 0;

protected:
	virtual void scanToken() = 0;

	virtual constexpr inline std::string getCurrentSubstring() noexcept {
		return src.substr(start, current - start);
	}

	virtual constexpr inline bool isAtEnd() const noexcept {
		return current >= src.size();
	}

	virtual constexpr inline bool match(const char ch) noexcept {
		if (isAtEnd() || peek() != ch) return false;

		current++;
		return true;
	}

	virtual constexpr inline char advance() noexcept {
		return src[current++];
	}

	virtual constexpr inline char peek() noexcept {
		return src[current];
	}

	virtual constexpr inline char peekNext() const noexcept {
		if (current + 1 >= src.size()) return '\0';
		return src[current + 1];
	}

	virtual constexpr inline char peekPrev() const noexcept {
		if (current - 1 < 0) return '\0';
		return src[current - 1];
	}

	std::string src;

	size_t start;
	size_t current;
};
