#pragma once

class OPUtil
{
public:
	// bitwise and
	constexpr static inline bool bwAnd(int left, int right) noexcept {
		return ((left & right) == right);
	}
};