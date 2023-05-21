#pragma once

#include <vector>

class VectorUtil
{
public:
	template <typename T>
	static inline bool exists(std::vector<T> src, T value) {
		return (std::find(src.begin(), src.end(), value) != src.end());
	}
};
