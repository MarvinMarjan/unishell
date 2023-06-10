#include "colorParser.h"

BaseColorStructure* ColorParser::parse()
{
	const std::string fMode = advance().getLexical();
	TokenList args;

	advance();

	args = getArgs();

	if (!args.size()) {
		if (!ignoreExceptions)
			throw SystemException(ColorParserError, "Argument expected", ExceptionRef(USER_INPUT, peek().getIndex()));

		return nullptr;
	}

	// color formats
	if (fMode == "id")	return getIdClrStructure(args);
	if (fMode == "rgb")	return getRGBClrStructure(args);
	if (fMode == "clr") return getClrStructure(args);

	else {
		if (ignoreExceptions) return nullptr;
		throw SystemException(ColorParserError, "Unknown color format", ExceptionRef(*System::input(), src[0].getIndex()));
	}

	// for safety
	return nullptr;
}


ColorParser::OperationResult ColorParser::checkArgsSize(const TokenList& args, const size_t minArgSize, Token& optionalMode) const
{
	// if args size is greater than minArgSize by two, then
	// throw a exception
	if (args.size() > minArgSize + 1) {
		if (ignoreExceptions) return Failure;
		throw SystemException(ColorParserError, "Number of arguments exceeded", ExceptionRef(USER_INPUT, args[args.size() - 1].getIndex()));
	}

	// if args size is greater than minArgSize by one,
	// then set optionalMode (color mode) to the last item in args
	if (args.size() > minArgSize)
		optionalMode = args[args.size() - 1];

	// args less than minArgSize
	else if (args.size() < minArgSize) {
		if (ignoreExceptions) return Failure;
		throw SystemException(ColorParserError, "Insufficient arguments", ExceptionRef(USER_INPUT, args[args.size() - 1].getIndex()));
	}

	// checks if optionalMode is valid
	if (!VectorUtil::exists(__colormode, optionalMode.getLexical())) {
		if (ignoreExceptions) return Failure;
		throw SystemException(ColorParserError, "Unknown color mode", ExceptionRef(USER_INPUT, args[args.size() - 1].getIndex()));
	}

	return Success;
}