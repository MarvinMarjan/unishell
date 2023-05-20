#pragma once

#include "../instream/token.h"

#include "../../outstream/outputColor.h"
#include "../../system/system.h"

#include "../../utilities/vectorUtil.h"

class ColorParser
{
public:
	ColorParser(TokenList src) : src(src) {
		current = 0;
	}

	BaseColorStructure* parse(bool ignoreExceptions = false) {
		std::string fMode = advance().getLexical();
		TokenList args;

		advance();

		args = getArgs();

		if (!args.size()) {
			if (!ignoreExceptions) throw SystemException(ColorParserError, "Argument expected", ExceptionRef(*System::input(), peek().getIndex()));
			return nullptr;
		}

		if (fMode == "id") return getIdClrStructure(args);
		if (fMode == "rgb") return getRGBClrStructure(args);
		if (fMode == "clr") return getClrStructure(args);

		else
			throw SystemException(ColorParserError, "Unknown color format", ExceptionRef(*System::input(), src[0].getIndex()));

		return nullptr;
	}

private:
	inline TokenList getArgs() {
		TokenList args;

		while (peek().getType() != COLON) {
			args.push_back(peek());
			advance();
		}

		return args;
	}


	// id color format
	inline IdColorStructure* getIdClrStructure(TokenList args) {
		Token optionalMode = Token(LITERAL, "normal", nullptr, {}, 0);

		checkArgsSize(args, IdColorStructure::argSize, optionalMode);
		checkTokenType({ args[0] }, NUMBER, "Number");

		return new IdColorStructure((int)asDbl(args[0].getLiteral()), stringToColorMode(optionalMode.getLexical()));
	}


	// rgb color format
	inline RGBColorStructure* getRGBClrStructure(TokenList args) {
		Token optionalMode = Token(LITERAL, "normal", nullptr, {}, 0);

		checkArgsSize(args, RGBColorStructure::argSize, optionalMode);
		checkTokenType({ args[0], args[1], args[2] }, NUMBER, "Number");

		return new RGBColorStructure(
			(int)asDbl(args[0].getLiteral()), (int)asDbl(args[1].getLiteral()), (int)asDbl(args[2].getLiteral()),
			stringToColorMode(optionalMode.getLexical())
		);
	}


	// predefined color format
	inline ColorStructure* getClrStructure(TokenList args) {
		Token optionalMode = Token(LITERAL, "normal", nullptr, {}, 0);

		checkArgsSize(args, ColorStructure::argSize, optionalMode);
		checkTokenType({ args[0] }, LITERAL, "Literal");

		if (!VectorUtil::exists(__color, asStr(args[0].getLiteral())))
			throw SystemException(ColorParserError, "Unknown color", ExceptionRef(*System::input(), args[0].getIndex()));

		return new ColorStructure(stringToColor(asStr(args[0].getLiteral())), stringToColorMode(optionalMode.getLexical()));
	}

	// throws a exception if args size is greater or lower 
	// than the expected or if color mode doesn't exists
	inline void checkArgsSize(TokenList args, size_t minArgSize, Token& optionalMode) {
		if (args.size() > minArgSize + 1)
			throw SystemException(ColorParserError, "Number of arguments exceeded", ExceptionRef(*System::input(), args[args.size() - 1].getIndex()));

		if (args.size() > minArgSize)
			optionalMode = args[args.size() - 1];

		else if (args.size() < minArgSize)
			throw SystemException(ColorParserError, "Insufficient arguments", ExceptionRef(*System::input(), args[args.size() - 1].getIndex()));

		if (!VectorUtil::exists(__colormode, optionalMode.getLexical()))
			throw SystemException(ColorParserError, "Unknown color mode", ExceptionRef(*System::input(), args[args.size() - 1].getIndex()));
	}

	// throws a exception if the type of a token in args is
	// not the expected
	inline void checkTokenType(TokenList args, TokenEnum expectedType, const std::string& expectedTypeStr) {
		for (Token token : args)
			if (token.getType() != expectedType)
				throw SystemException(ColorParserError, expectedTypeStr + " expected", ExceptionRef(*System::input(), token.getIndex()));
	}


	inline Token advance() {
		if (!isAtEnd()) current++;
		return prev();
	}

	inline Token peek() {
		return src[current];
	}

	inline Token prev() {
		if (!current) return src[current];
		return src[(size_t)current - 1];
	}

	inline bool isAtEnd() {
		return ((size_t)current >= src.size());
	}

	TokenList src;

	unsigned int current;
};
