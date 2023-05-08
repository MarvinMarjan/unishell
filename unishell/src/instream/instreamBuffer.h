#pragma once

#include <string>

class INStreamBuffer : public std::string
{
public:
	INStreamBuffer() : std::string() {
		cursorIndex = 0;
	}

	constexpr inline void cursorLeft() noexcept {
		cursorIndex--;
	}

	constexpr inline void cursorRight() noexcept {
		cursorIndex++;
	}

	constexpr inline int getCursorIndex() const noexcept {
		return cursorIndex;
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

	inline void eraseLast() noexcept {
		if (!size()) return;

		std::string buff = "";

		for (size_t i = 0; i < size() - 1; i++)
			buff += (*this)[i];

		assign(buff);

		cursorIndex--;
	}

	static inline std::string charToStr(char ch) noexcept {
		return std::string(1, ch);
	}

private:
	int cursorIndex;
};
