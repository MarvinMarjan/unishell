#include "tokenProcessing.h"

TokenList TokenProcess::generateColorTokens(TokenList source) {
	TokenList res;

	size_t start = 0, end = 0;

	for (size_t i = 0; i < source.size(); i++) {
		if (i + 1 < source.size() && source[i + 1].getType() == COLON) {
			start = i;
			i++;

			if (i + 1 >= source.size())
				throw SystemException(TokenProcessingError, "Unterminated color structure", ExceptionRef(*System::input(), System::input()->size() - 1));;

			i++;
			consume(source, COLON, i, "Unterminated color structure");

			end = i;

			res.push_back(Token(COLOR, "", nullptr, TokenList(source.begin() + start, source.begin() + end + 1), res.size() - 1));
		}

		else res.push_back(source[i]);
	}

	return res;
}

TokenList TokenProcess::parseTokens(TokenList source) {
	TokenList res;

	for (Token token : source) {
		switch (token.getType()) {
		case COLOR: {
			std::string parsed = ColorParser(token.getSub()).parse()->toString();
			res.push_back(Token(LITERAL, parsed, new LiteralValue(parsed), {}, token.getIndex()));
			break;
		}

		case EXPRESSION: {
			Expr* parsed = ExprParser(token.getSub(), *System::input()).parse();
			LiteralValue* interpreted = ExprInterpreter().interpret(parsed);
			TypeUtil::checkNull(interpreted);
			res.push_back(Token(TypeUtil::getTypeAsTokenEnum(getValueActiveType(interpreted)),
				TypeUtil::literalValueToString(interpreted), interpreted, {}, token.getIndex()));
			break;
		}

		default:
			res.push_back(token);
		}
	}

	return res;
}