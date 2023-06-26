#include "system_exception.h"


SystemException::SystemException(const SystemExceptionType type, const std::string& msg, const ExceptionRef& ref)
	: msg(msg), type(type), ref(ref)
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

	case SettingsError:
		typeMsg = "settings";
		break;

	default:
		typeMsg = "unknown";
	}
}

