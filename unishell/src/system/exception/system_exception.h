#pragma once

#include "exception_reference.h"
#include "../../outstream/color/color_chars.h"


#define NEW_USER_EXCEPTION(name, title) \
	class name : public UserException \
	{ \
	public: \
		name(const std::string& msg, const ExceptionRef& ref = ExceptionRef()) \
			: UserException(title, msg, ref) {} \
	}; \


#define NEW_EXCEPTION(name, title) \
	class name : public Exception \
	{ \
	public: \
		name(const std::string& msg) \
			: Exception(title, msg) {} \
	}; \



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


class UserException : public Exception
{
public:
	UserException(const std::string& title, const std::string& msg, const ExceptionRef& ref = ExceptionRef())
		: Exception(title, msg), ref_(ref) {}

	// formated error message
	std::string toString() const noexcept override {
		return clr('#' + title_, __clr_exception_title->toString()) + clr(" Error\n", __clr_exception_error->toString()) + ref_.getString() + "\n" + " > " + msg_ + '\n';
	}

protected:
	ExceptionRef ref_;
};


NEW_USER_EXCEPTION(ExprParserErr, "expression_parser")
NEW_USER_EXCEPTION(ExprInterpreterErr, "expression_interpreter")
NEW_USER_EXCEPTION(ColorParserErr, "color_parser")
NEW_USER_EXCEPTION(InstreamScannerErr, "instream_scanner")
NEW_USER_EXCEPTION(TokenProcessingErr, "token_processing")
NEW_USER_EXCEPTION(EnvironmentErr, "environment")
NEW_USER_EXCEPTION(CommandErr, "command")
NEW_USER_EXCEPTION(CommandRuntimeErr, "command_runtime")


NEW_EXCEPTION(SettingsErr, "settings")