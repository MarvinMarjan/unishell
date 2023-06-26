#pragma once

#include "../../system/global/typedecl.h"


namespace alg
{

namespace string
{


	constexpr inline std::string eraseLastCh(const std::string& src) noexcept {
		if (src.empty()) return src;
		return src.substr(0, src.size() - 1);
	}

	constexpr inline std::string eraseFirstCh(const std::string& src) noexcept {
		if (src.empty()) return src;
		return src.substr(1, src.size());
	}


	StringList split(const std::string& src, const char delimiter = ' ') noexcept;


	std::string toSnakeCase(const std::string& src) noexcept;

	std::string snakeCaseToPascal(const std::string& src) noexcept;


} // namespace string

} // namespace alg