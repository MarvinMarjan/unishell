#pragma once

#include "../outstream/outputColor.h"
#include "exceptionReference.h"

#include <string>

#define UNEXPECTED_TOKEN_MSG "Unexpected token"

enum SystemExceptionType
{
	ExprParserError,
	ColorParserError,
	InstreamScannerError,
	TokenProcessingError,
	EnvironmentError,
	InternalSystemError
};

class SystemException
{
public:
	SystemException(SystemExceptionType type, const std::string& msg, ExceptionRef ref = ExceptionRef("")) : msg(msg), type(type), ref(ref)
	{
		switch (type)
		{
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

		default:
			typeMsg = "unknown";
		}
	}

	// formated error message
	inline std::string toString() const noexcept {
		return clr('#' + typeMsg, 153) + clr(" Error\n", 196) + ref.getString() + "\n" + " > " + msg + '\n';
	}

private:
	std::string typeMsg; 
	std::string msg;
	ExceptionRef ref;

	SystemExceptionType type;
};