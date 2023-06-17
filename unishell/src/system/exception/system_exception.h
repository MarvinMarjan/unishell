#pragma once

#include "exception_reference.h"
#include "../../outstream/color/color_chars.h"


enum SystemExceptionType
{
	ExprInterpreterError,
	ExprParserError,
	ColorParserError,
	InstreamScannerError,
	TokenProcessingError,
	EnvironmentError,
	InternalSystemError,
	CommandError,
	CommandRuntimeError
};


class SystemException
{
public:
	SystemException(const SystemExceptionType type, const std::string& msg, const ExceptionRef& ref = ExceptionRef());

	// formated error message
	std::string toString() const noexcept {
		return clr('#' + typeMsg, 153) + clr(" Error\n", 196) + ref.getString() + "\n" + " > " + msg + '\n';
	}

private:
	std::string typeMsg; 
	std::string msg;
	ExceptionRef ref;

	SystemExceptionType type;
};


