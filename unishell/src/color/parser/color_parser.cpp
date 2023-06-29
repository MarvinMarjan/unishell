#include "color_parser.h"

BaseColorStructure* ColorParser::parse()
{
	const std::string fMode = advance().getLexical();
	TokenList args;

	advance();

	args = getArgs();

	if (!args.size()) {
		if (!ignoreExceptions)
			throw new ColorParserErr("Argument expected", ExceptionRef(UNISHLL_USER_INPUT, peek()));

		return nullptr;
	}

	// color formats
	if (fMode == "id")	return getIdClrStructure(args);
	if (fMode == "rgb")	return getRGBClrStructure(args);
	if (fMode == "clr") return getClrStructure(args);

	else if (ignoreExceptions) return nullptr;
		

	throw new ColorParserErr("Unknown color format", ExceptionRef(UNISHLL_USER_INPUT, src[0]));
}


ColorParser::OperationResult ColorParser::checkArgsSize(const TokenList& args, const size_t minArgSize, Token& optionalMode) const
{
	// if args size is greater than minArgSize plus one, then
	// throw a exception
	if (args.size() > minArgSize + 1) {
		if (ignoreExceptions) return Failure;
		throw new ColorParserErr("Number of arguments exceeded", ExceptionRef(UNISHLL_USER_INPUT, args[args.size() - 1]));
	}

	// if args size is greater than minArgSize,
	// then set optionalMode (color mode) to the last item in args
	if (args.size() > minArgSize)
		optionalMode = args[args.size() - 1];


	// args less than minArgSize
	else if (args.size() < minArgSize) {
		if (ignoreExceptions) return Failure;
		throw new ColorParserErr("Insufficient arguments", ExceptionRef(UNISHLL_USER_INPUT, args[args.size() - 1]));
	}


	// checks if optionalMode is valid
	if (!alg::vector::exists(__colormode, optionalMode.getLexical())) {
		if (ignoreExceptions) return Failure;
		throw new ColorParserErr("Unknown color mode", ExceptionRef(UNISHLL_USER_INPUT, args[args.size() - 1]));
	}

	return Success;
}