#pragma once

#include "stringUtil.h"

class VectorUtil
{
public:
	template <typename T1, typename T2>
	static inline std::vector<T2> map(std::vector<T1> src, T2 (*func)(T1 item)) {
		std::vector<T2> res;
		
		for (T1 item : src)
			res.push_back(func(item));

		return res;
	}

	template <typename T>
	static inline std::vector<size_t> findAll(std::vector<T> src, T value) {
		std::vector<size_t> occurrences;

		for (size_t i = 0; i < src.size(); i++)
			if (src[i] == value)
				occurrences.push_back(i);

		return occurrences;
	}

	static inline std::string join(StringList src, std::string sep = "") {
		std::string joined = "";

		for (size_t i = 0; i < src.size(); i++)
			joined += src[i] + ((i + 1 < src.size()) ? sep : "");

		return joined;
	}

	template <typename T>
	static inline bool exists(std::vector<T> src, T value) {
		return (std::find(src.begin(), src.end(), value) != src.end());
	}

	static inline StringList sortByCharacters(StringList src, std::string sortener) {
		StringList res;

		for (char ch : sortener)
			if (!StringUtil::isAlphaNumeric(ch))
				return {};

		for (std::string item : src)
			if (StringUtil::startsWith(item, sortener) && !VectorUtil::exists(res, item))
				res.push_back(item);

		if (res.empty() || sortener.empty()) return src;

		return res;
	}
};
