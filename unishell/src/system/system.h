#pragma once

#include <iostream>
#include <ShlObj.h>

#include "exception/systemException.h"
#include "windows/windowsSystem.h"

#include "../outstream/color/colorChars.h"
#include "../path/handler/pathHandler.h"
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
	static void printv(const Args&... args) noexcept {
		(std::cout << ... << args);
	}

	static void print(const std::string& text, const bool endLine = false) noexcept {
		std::cout << text;
		if (endLine) std::cout << std::endl;
	}

	// prints a error format message
	static void error(const SystemException& exception) noexcept {
		sysprintln(exception.toString());
	}

	static bool getAbort() noexcept {
		return abort;
	}

	constexpr static void exit() noexcept {
		abort = true;
	}



	static PathHandler* path() noexcept {
		return __workingPath;
	}

	static std::string* input() noexcept {
		return __userInput;
	}

	static Environment* env() noexcept {
		return __environment;
	}



	static Identifier* getEnvId(const std::string& idName, const int index = -1) {
		Identifier* identifier = __environment->getId(idName);

		if (!identifier)
			throw SystemException(EnvironmentError, "Unknown indentifier: " + idformat(idName), 
				(index != -1) ? ExceptionRef(*__userInput, index) : ExceptionRef(""));
		
		return identifier;
	}

	static void delEnvId(const std::string& idName) {
		if (__environment->exists(idName) && !__environment->isSysId(idName))
			__environment->delId(idName);
		else if (!__environment->isSysId(idName))
			throw SystemException(EnvironmentError, "Unknown identifier: " + idformat(idName));
		else
			throw SystemException(EnvironmentError, "Can't delete system identifiers.");
	}

private:
	static void addSysId(const std::string& name, LiteralValue* value) {
		__environment->addId(Identifier(name, value, true));
	}

	static bool abort;
};