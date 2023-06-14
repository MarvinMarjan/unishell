#pragma once

#include "../../system/global/typedecl.h"

namespace alg
{

namespace vector
{


	// return a list containing the strings in "src" that starts with "sortener"
	StringList sortByCharacters(const StringList& src, const std::string& sortener) noexcept;


} // namespace vector


} // namespace alg