#include "manip.h"


#include "../vector/item.h"
#include "char.h"


StringList alg::string::split(const std::string& src, const char delimiter) noexcept
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

std::string alg::string::toSnakeCase(const std::string& src) noexcept
{
	StringList list;

	for (const std::string& item : split(src))
		list.push_back(toLower(item));

	return alg::vector::join(list, "_");
}

std::string alg::string::snakeCaseToPascal(const std::string& src) noexcept
{
	StringList list;

	for (std::string item : split(src, '_')) {
		item[0] = toupper(item[0]);

		list.push_back(item);
	}

	return alg::vector::join(list, " ");
}
