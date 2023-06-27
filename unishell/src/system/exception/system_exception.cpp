#include "system_exception.h"


SystemException::SystemException(const SystemExceptionType type, const std::string& msg, const ExceptionRef& ref)
	: Exception("system", msg), type_(type), ref_(ref)
{
	switch (type)
	{
	case ExprInterpreterError:
		title_ = "expression_interpreter";
		break;

	case ExprParserError:
		title_ = "parser";
		break;

	case ColorParserError:
		title_ = "color_parser";
		break;

	case InstreamScannerError:
		title_ = "instream_scanner";
		break;

	case TokenProcessingError:
		title_ = "token_processing";
		break;

	case EnvironmentError:
		title_ = "environment";
		break;

	case InternalSystemError:
		title_ = "internal_system";
		break;

	case CommandError:
		title_ = "command";
		break;

	case CommandRuntimeError:
		title_ = "command_runtime";
		break;

	case SettingsError:
		title_ = "settings";
		break;

	default:
		title_ = "unknown";
	}
}

