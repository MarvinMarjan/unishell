#pragma once


namespace alg
{

namespace bit
{


	constexpr inline bool hasBits(const int bits, const int bit) noexcept {
		return ((bits & bit) == bit);
	}


} // namespace bit

} // namespace alg