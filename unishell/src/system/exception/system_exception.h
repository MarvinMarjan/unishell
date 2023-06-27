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
	CommandRuntimeError,

	SettingsError
};


class Exception
{
public:
	Exception(const std::string& title, const std::string& msg) : title_(title), msg_(msg) {}
	
	~Exception() = default;

	virtual std::string toString() const {
		return clr('#' + title_, __clr_exception_title->toString()) + clr(" Error\n", __clr_exception_error->toString()) + "\n" + " > " + msg_ + '\n';
	}

protected:
	std::string msg_;
	std::string title_;
};


class SystemException : public Exception
{
public:
	SystemException(const SystemExceptionType type, const std::string& msg, const ExceptionRef& ref = ExceptionRef());

	// formated error message
	std::string toString() const noexcept override {
		return clr('#' + title_, __clr_exception_title->toString()) + clr(" Error\n", __clr_exception_error->toString()) + ref_.getString() + "\n" + " > " + msg_ + '\n';
	}

private:
	ExceptionRef ref_;
	SystemExceptionType type_;
};