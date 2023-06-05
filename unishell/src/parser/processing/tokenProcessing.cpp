#include "tokenProcessing.h"

void TokenProcess::getInside(TokenList& res, TokenList source, TokenEnum lchar, TokenEnum rchar, TokenEnum resToken, const std::string& errMsg, bool processSub) {
	size_t start = 0, end = 0;
	unsigned short aux = 0;

	for (size_t i = 0; i < source.size(); i++) {
		if (source[i].getType() == lchar) {
			aux++;

			start = i;

			while (aux) {
				checkIndex(source, i, aux, errMsg);
				checkLRChar(source, i, aux, lchar, rchar);
			}

			end = i;

			TokenList sub = TokenList(source.begin() + start + 1, source.begin() + end);
			if (processSub) sub = process(sub);

			res.push_back(Token(resToken, "", nullptr, sub, source[end].getIndex()));
		}

		else res.push_back(source[i]);
	}
}

TokenList TokenProcess::generateColorTokens(TokenList source) {
	TokenList res;

	size_t start = 0, end = 0;

	for (size_t i = 0; i < source.size(); i++) {
		if (i + 1 < source.size() && source[i + 1].getType() == COLON) {
			start = i;
			i++;

			if (i + 1 >= source.size())
				throw SystemException(TokenProcessingError, "Unterminated color structure", ExceptionRef(USER_INPUT, System::input()->size() - 1));

			i++;
			consume(source, COLON, i, "Unterminated color structure");

			end = i;

			res.push_back(Token(COLOR, "", nullptr, TokenList(source.begin() + start, source.begin() + end + 1), source[end].getIndex()));
		}

		else res.push_back(source[i]);
	}

	return res;
}


TokenList TokenProcess::parseTokens(TokenList source) {
	TokenList res;

	for (Token token : source)
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
			res.push_back(Token(TypeUtil::getLitTokenEnum(interpreted),
				litToStr(interpreted), interpreted, {}, token.getIndex()));
			break;
		}

		default:
			res.push_back(token);
		}

	return res;
}


TokenList TokenProcess::expandRetCommands(TokenList source) {
	TokenList res;

	for (size_t i = 0; i < source.size(); i++) {
		Token token = source[i];

		switch (token.getType()) {
		case RETCOMMAND:
			res.push_back(getRetCommandReturn(source, i));
			break;

			// syntactic sugar for RETCOMMAND
			// "#cmd [arg]" same as "arg@cmd"
		case INRETCOMMAND:
			res.pop_back(); // remove previous literal if is INRETCOMMAND. it's used as first argument
			res.push_back(getRetCommandReturn(source, i, true));
			break;

		default:
			res.push_back(token);
		}
	}

	return res;
}


inline Token TokenProcess::getRetCommandReturn(TokenList source, size_t& i, bool integrate) {
	RetCommandBase* retCmd = nullptr;
	LiteralValue* ret = nullptr;
	TokenList list;
	ArgList args;
	FlagList flags;
	bool hasExplicitList = false;

	argsFromList(source, i, list);

	// don't encapsulate in RETCOMMANDS
	args = CmdUtil::getArgs(list, false, true, &hasExplicitList);
	flags = CmdUtil::getFlags(list);

	if (integrate)
		insertIntegrate(args, source[i - 1].getLiteral());

	retCmd = CmdUtil::getRetCommand(source[i].getLexical().substr(1), args, flags);

	if (!retCmd)
		throw SystemException(CommandError, "Unknown command: " + qtd(source[i].getLexical()));

	ret = retCmd->exec();

	if (hasExplicitList) i++;

	return Token(TypeUtil::getLitTokenEnum(ret), "", ret, {}, source[i].getIndex());
}