#pragma once

#include "exceptionReference.h"

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
	SystemException(const SystemExceptionType type, const std::string& msg, const ExceptionRef& ref = ExceptionRef()) : msg(msg), type(type), ref(ref)
	{
		switch (type)
		{
		case ExprInterpreterError:
			typeMsg = "expression_interpreter";
			break;

		case ExprParserError:
			typeMsg = "parser";
			break;

		case ColorParserError:
			typeMsg = "color_parser";
			break;

		case InstreamScannerError:
			typeMsg = "instream_scanner";
			break;

		case TokenProcessingError:
			typeMsg = "token_processing";
			break;

		case EnvironmentError:
			typeMsg = "environment";
			break;

		case InternalSystemError:
			typeMsg = "internal_system";
			break;

		case CommandError:
			typeMsg = "command";
			break;

		case CommandRuntimeError:
			typeMsg = "command_runtime";
			break;

		default:
			typeMsg = "unknown";
		}
	}

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