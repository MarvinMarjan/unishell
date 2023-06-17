#include "sort.h"

#include "../string/char.h"
#include "item.h"


StringList alg::vector::sortByCharacters(const StringList& src, const std::string& sortener) noexcept {
	StringList res;

	for (const char ch : sortener)
		if (!alg::string::isAlphaNumeric(ch))
			return {};

	for (const std::string& item : src)
		if (alg::string::startsWith(item, sortener) && !exists(res, item))
			res.push_back(item);

	if (res.empty() || sortener.empty()) return src;

	return res;
}


