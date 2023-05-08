#pragma once

#include <string>

enum DelHint
{
	CursorToEnd,
	CursorToBeg,
	Entire,

	delWindow_ScrollBuffer // Only supported in delWindow
};

inline std::string delLine(DelHint hint = CursorToEnd) noexcept {
	return "\033[" + std::to_string(hint) + "K";
}

inline std::string delWindow(DelHint hint = CursorToEnd) noexcept {
	return "\033[" + std::to_string(hint) + "J";
}

inline std::string saveCursor() {
	return "\033[s";
}

inline std::string loadCursor() {
	return "\033[u";
}

inline std::string cursorUp() {
	return "\033[A";
}

inline std::string cursorDown() {
	return "\033[B";
}

inline std::string cursorRight() {
	return "\033[C";
}

inline std::string cursorLeft() {
	return "\033[D";
}

inline std::string scrollUp() {
	return "\033[S";
}

inline std::string scrollDown() {
	return "\033[T";
}
