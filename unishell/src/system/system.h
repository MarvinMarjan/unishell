#pragma once

#include <iostream>
#include <Windows.h>
#include <ShlObj.h>

#include "systemException.h"
#include "windowsSystem.h"

#include "../outstream/outputColor.h"
#include "../path/pathHandler.h"

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

	// prints a error format message
	static inline void error(const SystemException& exception) noexcept {
		sysprintln(exception.toString());
	}

	constexpr static inline bool getAbort() noexcept {
		return abort;
	}

	constexpr static inline void exit() noexcept {
		abort = true;
	}



	static inline PathHandler* path() noexcept {
		return GLOBAL_workingPath;
	}

	static inline std::string* input() noexcept {
		return GLOBAL_userInput;
	}

private:
	static bool abort;

	static PathHandler* GLOBAL_workingPath; // static variable for storing the current working directory path
	static std::string* GLOBAL_userInput;   // static variable for storing the last user input raw string
};