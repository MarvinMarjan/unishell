#pragma once

#include "../utilities/stringUtil.h"

class INSSearchList : private StringList
{
public:
	INSSearchList() {
		index = 0;
		sequence = false;
	}

	inline void set(const StringList& other) {
		if (sequence) return;
		*((StringList*)this) = other;
		index = 0;
	}

	inline void next() noexcept {
		if (index + 1 >= size()) index = 0;
		else index++;
	}

	inline std::string get() const noexcept {
		return (*this)[index];
	}

	inline StringList getList() const noexcept {
		return *((StringList*)this);
	}

	bool sequence;

private:
	int index;
};