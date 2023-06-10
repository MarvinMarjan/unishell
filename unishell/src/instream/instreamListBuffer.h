#pragma once

#include "../utilities/stringUtil.h"

class INSListBuffer : private StringList
{
public:
	constexpr inline INSListBuffer() : StringList() {
		current = 0;
		ignoreCurrentIndexChange = true;
	}

	constexpr void reset() noexcept {
		ignoreCurrentIndexChange = true;
		current = (current > 0) ? size() - 1 : 0;
	}

	constexpr void add(const std::string& value) {
		if (current > 0 && value == at(current)) return;
		
		push_back(value);
		current = size() - 1;
	}
	
	constexpr void up() noexcept {
		if (current > 0) current--;

		if (ignoreCurrentIndexChange) {
			ignoreCurrentIndexChange = false;
			down();
		}
	}

	constexpr void down() noexcept {
		if (current < size() - 1) current++;

		if (ignoreCurrentIndexChange) {
			ignoreCurrentIndexChange = false;
			up();
		}
	}

	constexpr std::string get() noexcept {
		if (size() && current < size()) return (*this)[current];
		return std::string();
	}

	bool ignoreCurrentIndexChange;

private:
	size_t current;
};
