#pragma once

#include "../utilities/stringUtil.h"

class INSListBuffer : private StringList
{
public:
	INSListBuffer() : StringList() {
		current = 0;
		ignoreCurrentIndexChange = true;
	}

	inline void reset() noexcept {
		ignoreCurrentIndexChange = true;
		current = size() - 1;
	}

	inline void add(const std::string& value) {
		if (std::find(begin(), end(), value) != end()) return;

		push_back(value);
		current = size() - 1;
	}
	
	inline void up() noexcept {
		if (current > 0) current--;

		if (ignoreCurrentIndexChange) {
			ignoreCurrentIndexChange = false;
			down();
		}
	}

	inline void down() noexcept {
		if (current < size() - 1) current++;

		if (ignoreCurrentIndexChange) {
			ignoreCurrentIndexChange = false;
			up();
		}
	}

	inline std::string get() noexcept {
		if (size() && current < size()) return (*this)[current];
	}

	bool ignoreCurrentIndexChange;

private:
	size_t current;
};
