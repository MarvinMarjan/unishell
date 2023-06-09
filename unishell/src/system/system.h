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
#define sysprintv		System::printv
#define sysprintln(msg) System::print(msg, true)

#define USER_INPUT *System::input()

class System
{
public:
	System();

	template <typename... Args>
	static inline void printv(const Args&... args) noexcept {
		(std::cout << ... << args);
	}

	static inline void print(const std::string& text, bool endLine = false) noexcept {
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



	constexpr static inline PathHandler* path() noexcept {
		return __workingPath;
	}

	constexpr static inline std::string* input() noexcept {
		return __userInput;
	}

	constexpr static inline Environment* env() noexcept {
		return __environment;
	}



	static inline Identifier* getEnvId(const std::string& idName, int index = -1) {
		Identifier* identifier = __environment->getId(idName);

		if (!identifier)
			throw SystemException(EnvironmentError, "Unknown indentifier: " + idformat(idName), 
				(index != -1) ? ExceptionRef(*__userInput, index) : ExceptionRef(""));
		
		return identifier;
	}

	static inline void delEnvId(const std::string& idName) {
		if (__environment->exists(idName) && !__environment->isSysId(idName))
			__environment->delId(idName);
		else if (!__environment->isSysId(idName))
			throw SystemException(EnvironmentError, "Unknown identifier: " + idformat(idName));
		else
			throw SystemException(EnvironmentError, "Can't delete system identifiers.");
	}

private:
	static inline void addSysId(const std::string& name, LiteralValue* value) {
		__environment->addId(Identifier(name, value, true));
	}

	static bool abort;
};