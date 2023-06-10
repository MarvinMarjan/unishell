#pragma once

#include "stringUtil.h"

class VectorUtil
{
public:
	template <typename T1, typename T2>
	static std::vector<T2> map(const std::vector<T1>& src, T2 (*func)(T1 item)) {
		std::vector<T2> res;
		
		for (const T1& item : src)
			res.push_back(func(item));

		return res;
	}

	template <typename T>
	static std::vector<size_t> findAll(const std::vector<T>& src, const T& value) noexcept {
		std::vector<size_t> occurrences;

		for (size_t i = 0; i < src.size(); i++)
			if (src[i] == value)
				occurrences.push_back(i);

		return occurrences;
	}

	static std::string join(const StringList& src, const std::string& sep = "") noexcept {
		std::string joined = "";

		for (size_t i = 0; i < src.size(); i++)
			joined += src[i] + ((i + 1 < src.size()) ? sep : "");

		return joined;
	}

	template <typename T>
	constexpr static bool exists(const std::vector<T>& src, const T& value) {
		return (std::find(src.begin(), src.end(), value) != src.end());
	}

	constexpr static StringList sortByCharacters(const StringList& src, const std::string& sortener) noexcept {
		StringList res;

		for (char ch : sortener)
			if (!StringUtil::isAlphaNumeric(ch))
				return {};

		for (const std::string& item : src)
			if (StringUtil::startsWith(item, sortener) && !VectorUtil::exists(res, item))
				res.push_back(item);

		if (res.empty() || sortener.empty()) return src;

		return res;
	}
};
