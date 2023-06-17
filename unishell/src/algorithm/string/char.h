#pragma once

#include "../vector/item.h"

#include <string>
#include <Windows.h>

extern const std::string __word_separator;


namespace alg
{

namespace string
{


	constexpr inline bool isAlpha(const char ch) noexcept {
		return (ch >= 'a' && ch <= 'z') ||
			(ch >= 'A' && ch <= 'Z') ||
			(ch == '_');
	}

	constexpr inline bool isDigit(const char ch) noexcept {
		return (ch >= '0' && ch <= '9') || ch == '.';
	}

	constexpr inline bool isAlphaNumeric(const char ch) noexcept {
		return isAlpha(ch) || isDigit(ch);
	}

	constexpr inline bool isMathOperator(const char ch) noexcept {
		return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')');
	}

	constexpr inline bool isComparisonOperator(const char ch) noexcept {
		return (ch == '=' || ch == '!' || ch == '>' || ch == '<');
	}

	constexpr inline bool isEncloseChar(const char ch) noexcept {
		return (ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '{' || ch == '}' || ch == ':');
	}

	constexpr inline bool isSeparator(const char ch) noexcept {
		return (ch == ',' || ch == ';');
	}

	constexpr inline bool isEmptyChar(const char ch) noexcept {
		return (ch == ' ' || ch == '\t');
	}

	constexpr inline bool isWordSeparator(const char ch) noexcept {
		return __word_separator.find(ch);
	}


	constexpr inline std::string charToStr(const char ch) noexcept {
		return std::string(1, ch);
	}
	

	inline std::string toUpper(const std::string& src) noexcept {
		std::string res = "";

		for (const char ch : src)
			res += std::toupper(ch);

		return res;
	}


	inline std::string toLower(const std::string& src) noexcept {
		std::string res = "";

		for (const char ch : src)
			res += std::tolower(ch);

		return res;
	}


	constexpr inline bool startsWith(const std::string& src, const std::string& sub) noexcept {
		return (src.size() >= sub.size() && src.substr(0, sub.size()) == sub);
	}


	constexpr inline size_t findLast(const std::string& src, const char ch) noexcept {
		size_t index = SIZE_MAX;

		for (size_t i = 0; i < src.size(); i++)
			if (src[i] == ch)
				index = i;

		return index;
	}

	constexpr inline size_t findFirst(const std::string& src, const char ch) noexcept {
		for (size_t i = 0; i < src.size(); i++)
			if (src[i] == ch)
				return i;

		return SIZE_MAX;
	}


	// using Windows API for conversion. wstring_convert is deprecated since C++17
	inline char* wcharToChar(const wchar_t* wchar) {
		const int len = WideCharToMultiByte(CP_UTF8, 0, wchar, -1, nullptr, 0, nullptr, nullptr);
		char* charStr = new char[len];
		WideCharToMultiByte(CP_UTF8, 0, wchar, -1, charStr, len, nullptr, nullptr);

		return charStr;
	}

	inline wchar_t* charToWchar(const char* ch) {
		const int len = MultiByteToWideChar(CP_UTF8, 0, ch, -1, NULL, 0);
		wchar_t* wchar = new wchar_t[len];
		MultiByteToWideChar(CP_UTF8, 0, ch, -1, wchar, len);

		return wchar;
	}


	inline std::string wstringToString(const std::wstring& wstr) noexcept {
		return std::string(wcharToChar(wstr.c_str()));
	}


} // namespace string

} // namespace alg