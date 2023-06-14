#include "manip.h"

StringList alg::string::split(const std::string& src, const char delimiter = ' ') noexcept
{
	StringList vec;
	std::string aux = "";

	for (size_t i = 0; i < src.size(); i++) {
		if (src[i] == delimiter) {
			vec.push_back(aux);
			aux = "";
			continue;
		}

		aux += src[i];
	}

	vec.push_back(aux);

	return vec;
}