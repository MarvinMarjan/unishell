#pragma once


#include <string>


class INStreamBuffer : public std::string
{
public:
	INStreamBuffer() : std::string() {
		cursorIndex = 0;
	}

	constexpr void cursorLeft() noexcept {
		if (cursorIndex > 0) cursorIndex--;
	}

	constexpr void cursorRight() noexcept {
		if (cursorIndex < size()) cursorIndex++;
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

private:
	int cursorIndex;
};
