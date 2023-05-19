#pragma once

#include <iostream>
#include <Windows.h>
#include <ShlObj.h>

#include "systemException.h"
#include "windowsSystem.h"

#include "../outstream/outputColor.h"
#include "../path/pathHandler.h"
#include "../environment/environment.h"

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

	static inline Environment* env() noexcept {
		return GLOBAL_environment;
	}

	static inline Identifier* getEnvId(const std::string& idName, int index = -1) {
		Identifier* identifier = GLOBAL_environment->getId(idName);

		if (!identifier)
			throw SystemException(EnvironmentError, "Unknown indentifier: " + clr(idName, __clr_identifier), 
				(index != -1) ? ExceptionRef(*GLOBAL_userInput, index) : ExceptionRef(""));
		
		return identifier;
	}

private:
	static bool abort;

	static Environment* GLOBAL_environment; // stores a Environment pointer
	static PathHandler* GLOBAL_workingPath; // stores the current working directory path
	static std::string* GLOBAL_userInput;   // stores the last user input raw string
};