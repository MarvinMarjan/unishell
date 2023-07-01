#pragma once

#include <iostream>
#include <ShlObj.h>

#include "exception/system_exception.h"
#include "windows/windows_system.h"

#include "../path/handler/path_handler.h"
#include "../environment/environment.h"

#include "settings/settings.h"


#define sysprint        System::print
#define sysprintv		System::printv
#define sysprintln(msg) System::print(msg, true)

#define UNISHLL_NAME	"unishell"
#define UNISHLL_OS		"Windows"

#define UNISHLL_USER_INPUT *System::input()


struct SysStat
{
	bool settingJsonFileLoadFailed;
};


class System
{
public:
	System();

	template <typename... Args>
	static void printv(const Args&... args) noexcept {
		std::cout << std::boolalpha;
		(std::cout << ... << args);
	}

	static void print(const std::string& text, const bool endLine = false) noexcept {
		std::cout << text;
		if (endLine) std::cout << std::endl;
	}


	// prints a error format message
	static void error(const Exception& exception) noexcept {
		sysprintln(exception.toString());
	}

	static void error(Exception* exception) noexcept {
		sysprintln(exception->toString());

		delete exception;
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



	static Identifier* getEnvId(const std::string& idName, const int index = -1, const int line = 1);

	static void delEnvId(const std::string& idName);

private:
	static void addSysId(const std::string& name, lit::LiteralValue* value) {
		__environment->addId(Identifier(name, value, true));
	}

	static bool abort;
};