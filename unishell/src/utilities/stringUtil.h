#pragma once

#include <string>
#include <sstream>
#include <vector>

#include <Windows.h>

typedef std::vector<std::string> StringList;

extern const std::string __word_separator;

class StringUtil
{
public:
	// is a letter or a number
	constexpr static inline bool isAlphaNumeric(char ch) noexcept {
		return isAlpha(ch) || isDigit(ch);
	}

	// is a letter
	constexpr static inline bool isAlpha(char ch) noexcept {
		return (ch >= 'a' && ch <= 'z') ||
			   (ch >= 'A' && ch <= 'Z') ||
			   (ch == '_');
	}

	// is a number
	constexpr static inline bool isDigit(char ch) noexcept {
		return (ch >= '0' && ch <= '9') || ch == '.';
	}

	// is math operators
	constexpr static inline bool isMathOperator(char ch) noexcept {
		return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')');
	}

	// is comparision operators
	constexpr static inline bool isComparisonOperator(char ch) noexcept {
		return (ch == '=' || ch == '!' || ch == '>' || ch == '<');
	}

	constexpr static inline bool isEncloseChar(char ch) noexcept {
		return (ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '{' || ch == '}' || ch == ':');
	}

	constexpr static inline bool isSeparator(char ch) noexcept {
		return (ch == ',' || ch == ';');
	}

	constexpr static inline bool isIgnoredChar(char ch) noexcept {
		return (ch == ' ' || ch == '\t');
	}

	static inline std::string toUpper(const std::string& src) noexcept {
		std::string res = "";

		for (char ch : src)
			res += std::toupper(ch);

		return res;
	}

	static inline std::string toLower(const std::string& src) noexcept {
		std::string res = "";

		for (char ch : src)
			res += std::tolower(ch);

		return res;
	}

	static inline bool isWordSeparator(char ch) noexcept {
		return (std::find(__word_separator.begin(), __word_separator.end(), ch) != __word_separator.end());
	}

	static inline bool startsWith(const std::string& src, const std::string& sub) noexcept {
		if (src.size() < sub.size()) return false;

		if (src.substr(0, sub.size()) == sub)
			return true;

		return false;
	}

	static inline size_t findLast(const std::string& src, char ch) noexcept {
		size_t index = 0;

		for (size_t i = 0; i < src.size(); i++)
			if (src[i] == ch)
				index = i;

		return index;
	}

	static inline std::string eraseLast(const std::string& src) noexcept {
		if (!src.size()) return src;
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
		const int len = WideCharToMultiByte(CP_UTF8, 0, wchar, -1, nullptr, 0, nullptr, nullptr);
		char* charStr = new char[len];
		WideCharToMultiByte(CP_UTF8, 0, wchar, -1, charStr, len, nullptr, nullptr);
		
		return charStr;
	}

	static inline wchar_t* charToWchar(const char* ch) {
		const int len = MultiByteToWideChar(CP_UTF8, 0, ch, -1, NULL, 0);
		wchar_t* wchar = new wchar_t[len];
		MultiByteToWideChar(CP_UTF8, 0, ch, -1, wchar, len);

		return wchar;
	}

	// converts a char into a std::string
	static inline std::string charToStr(char ch) noexcept {
		return std::string(1, ch);
	}
};