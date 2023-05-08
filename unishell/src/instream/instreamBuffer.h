#pragma once

#include <string>

#define INSCharToStr INStreamBuffer::charToStr

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

	static inline std::vector<std::string> split(const std::string& src, char delimiter = ' ') {
		std::vector<std::string> vec;
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

private:
	int cursorIndex;
};
