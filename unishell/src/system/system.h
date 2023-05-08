#pragma once

#include <iostream>
#include <Windows.h>

#include "systemException.h"
#include "../outstream/outputColor.h"

#define sysprint        System::print
#define sysprintln(msg) System::print(msg, true)

class System
{
public:
	System() {}

	static inline void print(const std::string& text, bool endLine = false) {
		std::cout << text;
		if (endLine) std::cout << std::endl;
	}

	static inline void error(const SystemException& exception) noexcept {
		error(exception.toString());
	}

	static inline void error(const std::string& errMsg) noexcept {
		std::cout << clr("Error: ", red) << errMsg << std::endl;
	}

	static inline void warning(const std::string& warnMsg) noexcept {
		std::cout << clr("Warning: ", wyellow) << warnMsg << std::endl;
	}

	static inline void message(const std::string& msg) noexcept {
		std::cout << clr("Message: ", wcyan) << msg << std::endl;
	}

	constexpr static inline bool getAbort() noexcept {
		return abort;
	}

	constexpr static inline void exit() noexcept {
		abort = true;
	}

	static inline void setCursorVisible(bool visible) {
		CONSOLE_CURSOR_INFO info = { 1, visible };
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	}

private:
	static bool abort;
};