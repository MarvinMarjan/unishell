#pragma once

class OPUtil
{
public:
	// bitwise and
	constexpr static bool bwAnd(const int left, const int right) noexcept {
		return ((left & right) == right);
	}
};