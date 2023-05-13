#pragma once

#include "../utilities/stringUtil.h"

#include <string>

class INStreamBuffer : public std::string
{
public:
	INStreamBuffer() : std::string() {
		cursorIndex = 0;
	}

	inline void cursorLeft() noexcept {
		if (cursorIndex > 0) cursorIndex--;
	}

	inline void cursorRight() noexcept {
		if (cursorIndex < size() - 1) cursorIndex++;
	}

	constexpr inline int getCursorIndex() const noexcept {
		return cursorIndex;
	}

	constexpr inline void setCursorIndex(int index) noexcept {
		cursorIndex = index;
	}

	inline void insertStr(size_t index, const std::string& text) {
		insert(index, text.c_str());
		cursorIndex++;
	}

	inline void eraseAtIndex(int index) {
		if (index < 0) return;

		std::string buff = "";

		for (size_t i = 0; i < size(); i++)
			if ((int) i != index)
				buff += (*this)[i];

		assign(buff);

		cursorIndex--;
	}

private:
	int cursorIndex;
};
