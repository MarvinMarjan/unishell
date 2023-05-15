#pragma once

#include <string>
#include <sstream>
#include <vector>

#include <Windows.h>

typedef std::vector<std::string> StringList;

class StringUtil
{
public:
	constexpr static inline bool isAlphaNumeric(char ch) noexcept {
		return isAlpha(ch) || isDigit(ch);
	}

	constexpr static inline bool isAlpha(char ch) noexcept {
		return (ch >= 'a' && ch <= 'z') ||
			   (ch >= 'A' && ch <= 'Z') ||
			   (ch == '_');
	}

	constexpr static inline bool isDigit(char ch) noexcept {
		return (ch >= '0' && ch <= '9') || ch == '.';
	}

	constexpr static inline bool isMathOperator(char ch) noexcept {
		return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')');
	}

	constexpr static inline bool isComparisonOperator(char ch) noexcept {
		return (ch == '=' || ch == '!' || ch == '>' || ch == '<');
	}

	static inline size_t findLast(const std::string& src, char ch) {
		size_t index = 0;

		for (size_t i = 0; i < src.size(); i++)
			if (src[i] == ch)
				index = i;

		return index;
	}

	static inline std::string eraseLast(const std::string& src) {
		return src.substr(0, src.size() - 1);
	}

	static inline StringList split(const std::string& src, char delimiter = ' ') noexcept {
		StringList vec;
		std::string aux = "";

		for (size_t i = 0; i < src.size(); i++) {
			if (src[i] == delimiter) {
				vec.push_back(aux);
				aux = "";
				continue;
			}

			aux += src[i];
		}

		vec.push_back(aux);

		return vec;
	}

	static inline std::string wstringToString(const std::wstring& wstr) noexcept {
		return std::string(wcharToChar(wstr.c_str()));
	}

	// using Windows API for conversion. wstring_convert is deprecated since C++17
	static inline char* wcharToChar(const wchar_t* wchar) {
		int len = WideCharToMultiByte(CP_UTF8, 0, wchar, -1, nullptr, 0, nullptr, nullptr);
		char* charStr = new char[len];
		WideCharToMultiByte(CP_UTF8, 0, wchar, -1, charStr, len, nullptr, nullptr);
		
		return charStr;
	}

	static inline std::string charToStr(char ch) noexcept {
		return std::string(1, ch);
	}
};