#pragma once

#include <string>
#include <vector>
#include <codecvt>

#define UTCharToStr StringUtil::charToStr
#define UTFromWStr  StringUtil::wstringToString

class StringUtil
{
public:
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

	static inline std::vector<std::string> split(const std::string& src, char delimiter = ' ') noexcept {
		std::vector<std::string> vec;
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

	static inline std::string wstringToString(const std::wstring& src) noexcept {
		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		std::string str = converter.to_bytes(src);

		return str;
	}

	static inline std::string charToStr(char ch) noexcept {
		return std::string(1, ch);
	}
};