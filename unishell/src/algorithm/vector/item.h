#pragma once

#include "../../system/global/typedecl.h"

#include <algorithm>


namespace alg
{

namespace vector
{

	
	// returns true if "value" exists in "src"
	template <typename T>
	constexpr inline bool exists(const std::vector<T>& src, const T& value) {
		return (std::find(src.begin(), src.end(), value) != src.end());
	}


	// execute "func" for every item in "src" and
	// return a vector containing the returns of "func"
	template <typename T1, typename T2>
	inline std::vector<T2> map(const std::vector<T1>& src, T2 (*func)(T1)) {
		std::vector<T2> res;

		for (const T1& item : src)
			res.push_back(func(item));

		return res;
	}

	// execute "func" for every item in "src" and
	// return a vector containing the items that "func"
	// returned true
	template <typename T>
	inline std::vector<T> filter(const std::vector<T>& src, bool (*func)(T)) {
		std::vector<T> res;

		for (const T& item : src)
			if (func(item))
				res.push_back(item);

		return res;
	}


	// returns a vector containing all indexes of "value" occurrence in "src
	template <typename T>
	inline std::vector<size_t> findAll(const std::vector<T>& src, const T& value) noexcept {
		std::vector<size_t> occurrences;

		for (size_t i = 0; i < src.size(); ++i)
			if (src[i] == value)
				occurrences.push_back(i);

		return occurrences;
	}


	// joins every string in "src" in "joined" by "sep" separator
	inline std::string join(const StringList& src, const std::string& sep = "") noexcept {
		std::string joined = "";

		for (size_t i = 0; i < src.size(); i++)
			joined += src[i] + ((i + 1 < src.size()) ? sep : "");

		return joined;
	}

} // namespace vector


} // namespace alg
