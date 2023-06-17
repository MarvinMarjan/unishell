#pragma once

#include "../../instream/scanner/instream_token.h"
#include "../../system/system.h"
#include "../../algorithm/vector/item.h"

class ColorParser
{
public:
	explicit ColorParser(const TokenList& src, const bool ignoreExceptions = false) : 
		src(src), ignoreExceptions(ignoreExceptions)
	{
		current = 0;
	}

	// returns a string representation of the source color
	BaseColorStructure* parse();

private:
	// Failure for exceptions, but ignoreExceptions is true
	// Success for everything is okay
	enum OperationResult { Success, Failure };


	TokenList getArgs() {
		TokenList args;

		// gets all tokens before a COLON
		while (peek().getType() != COLON) {
			args.push_back(peek());
			advance();
		}

		return args;
	}


	// id color format
	IdColorStructure* getIdClrStructure(const TokenList& args) const
	{
		Token optionalMode = Token(LITERAL, "normal", nullptr, {}, 0);

		if (checkArgsSize(args, IdColorStructure::argSize, optionalMode) == Failure) return nullptr;
		if (checkTokenType({ args[0] }, NUMBER, "Number") == Failure) return nullptr;

		return new IdColorStructure((int)asDbl(args[0].getLiteral()), stringToColorMode(optionalMode.getLexical()));
	}


	// rgb color format
	RGBColorStructure* getRGBClrStructure(const TokenList& args) const
	{
		Token optionalMode = Token(LITERAL, "normal", nullptr, {}, 0);

		if (checkArgsSize(args, RGBColorStructure::argSize, optionalMode) == Failure) return nullptr;
		if (checkTokenType({ args[0], args[1], args[2] }, NUMBER, "Number") == Failure) return nullptr;

		return new RGBColorStructure(
			(int)asDbl(args[0].getLiteral()), (int)asDbl(args[1].getLiteral()), (int)asDbl(args[2].getLiteral()),
			stringToColorMode(optionalMode.getLexical())
		);
	}


	// predefined color format
	ColorStructure* getClrStructure(const TokenList& args) const
	{
		Token optionalMode = Token(LITERAL, "normal", nullptr, {}, 0);

		if (checkArgsSize(args, ColorStructure::argSize, optionalMode) == Failure) return nullptr;
		if (checkTokenType({ args[0] }, LITERAL, "Literal") == Failure) return nullptr;

		if (!alg::vector::exists(__color, asStr(args[0].getLiteral())) && !ignoreExceptions) {
			if (ignoreExceptions) return nullptr;
			throw SystemException(ColorParserError, "Unknown color", ExceptionRef(*System::input(), args[0].getIndex()));
		}

		return new ColorStructure(stringToColor(asStr(args[0].getLiteral())), stringToColorMode(optionalMode.getLexical()));
	}

	// throws a exception if args size is greater or lower 
	// than the expected or if color mode doesn't exists
	OperationResult checkArgsSize(const TokenList& args, const size_t minArgSize, Token& optionalMode) const;
	

	// throws a exception if the type of a token in args is
	// not the expected
	OperationResult checkTokenType(const TokenList& args, const TokenEnum expectedType, const std::string& expectedTypeStr) const {
		for (const Token& token : args) {
			if (token.getType() != expectedType) {
				if (ignoreExceptions) return Failure;
				throw SystemException(ColorParserError, expectedTypeStr + " expected", ExceptionRef(*System::input(), token.getIndex()));
			}
		}

		return Success;
	}


	Token advance() noexcept {
		if (!isAtEnd()) current++;
		return prev();
	}

	Token peek() const noexcept {
		return src[current];
	}

	Token prev() const noexcept {
		if (!current) return src[current];
		return src[(size_t)current - 1];
	}

	bool isAtEnd() const noexcept {
		return ((size_t)current >= src.size());
	}

	TokenList src;

	unsigned int current;
	bool ignoreExceptions;
};
