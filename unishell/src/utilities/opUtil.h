#pragma once

class OPUtil
{
public:
	constexpr static inline bool bwAnd(int left, int right) noexcept {
		return ((left & right) == right);
	}
};