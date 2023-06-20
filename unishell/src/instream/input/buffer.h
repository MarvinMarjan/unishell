#pragma once


#include "../../algorithm/string/char.h"

#include <string>


extern const std::string __word_separator;


class INStreamBuffer : public std::string
{
public:
	INStreamBuffer() : std::string() {
		cursorIndex = 0;
	}

	constexpr void cursorLeft(const bool untilSeparator = false) noexcept {
		if (cursorIndex > 0) {
			if (untilSeparator) 
				while (!alg::string::isWordSeparator(at(cursorIndex - 1))) cursorIndex--;
			else
				cursorIndex--;
		}
	}

	constexpr void cursorRight(const bool untilSeparator = false) noexcept {
		if (cursorIndex < size()) {
			if (untilSeparator)
				while (!alg::string::isWordSeparator(at(cursorIndex - 1))) cursorIndex++;
			else
				cursorIndex++;
		}
	}

	constexpr int getCursorIndex() const noexcept {
		return cursorIndex;
	}

	constexpr void setCursorIndex(int index) noexcept {
		cursorIndex = index;
	}

	constexpr void insertStr(const size_t index, const std::string& text) {
		insert(index, text.c_str());
		cursorIndex++;
	}

	constexpr void eraseAtIndex() {
		if (getCursorIndex() - 1 < 0) return;
		erase((size_t)getCursorIndex() - 1, 1);
		cursorLeft();
	}

	void eraseUntilSeparator() {
		if (cursorIndex - 1 >= 0 && alg::string::isWordSeparator(at(cursorIndex - 1))) {
			eraseAtIndex();
			return;
		}

		while (cursorIndex - 1 >= 0 && !alg::string::isWordSeparator(at(cursorIndex - 1)))
			eraseAtIndex();
	}

private:
	int cursorIndex;
};
