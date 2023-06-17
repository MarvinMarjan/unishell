#pragma once

#include <string>

enum DelHint
{
	CursorToEnd,
	CursorToBeg,
	Entire,

	delWindow_ScrollBuffer // Only supported in delWindow
};

inline std::string delLine(const DelHint hint = CursorToEnd) noexcept {
	return "\033[" + std::to_string(hint) + "K";
}

inline std::string delWindow(const DelHint hint = CursorToEnd) noexcept {
	return "\033[" + std::to_string(hint) + "J";
}

constexpr inline std::string saveCursor() noexcept {
	return "\033[s";
}

constexpr inline std::string loadCursor() noexcept {
	return "\033[u";
}

constexpr inline std::string cursorUp() noexcept {
	return "\033[A";
}

constexpr inline std::string cursorDown() noexcept {
	return "\033[B";
}

constexpr inline std::string cursorRight() noexcept {
	return "\033[C";
}

constexpr inline std::string cursorLeft() noexcept {
	return "\033[D";
}

constexpr inline std::string scrollUp() noexcept {
	return "\033[S";
}

constexpr inline std::string scrollDown() noexcept {
	return "\033[T";
}
