#include "tokenProcessing.h"

TokenList TokenProcess::subToLiteral(const TokenList& source)
{
	TokenList res;

	for (const Token& token : source)
		switch (token.getType()) {
		case LIST: {
			if (token.getLiteral()) {
				res.push_back(token);
				break;
			}

			const TokenList parsed = process(token.getSub());
			res.push_back(Token(LIST, "", getListFromTokenList(parsed), {}, token.getIndex()));
			break;
		}

		case OBJECT: {
			if (token.getLiteral()) {
				res.push_back(token);
				break;
			}

			const TokenList parsed = process(token.getSub());
			res.push_back(Token(OBJECT, "", getObjFromTokenList(parsed), {}, token.getIndex()));
			break;
		}

		default:
			res.push_back(token);
		}

	return res;
}

void TokenProcess::getInside(TokenList& res, const TokenList& source, const TokenEnum lchar, const TokenEnum rchar, 
	const TokenEnum resToken, const std::string& errMsg, const bool processSub)
{
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

			// recursive processing
			TokenList sub = TokenList(source.begin() + start + 1, source.begin() + end);
			if (processSub) sub = process(sub);

			res.push_back(Token(resToken, "", nullptr, sub, source[end].getIndex()));
		}

		else res.push_back(source[i]);
	}
}

TokenList TokenProcess::generateColorTokens(const TokenList& source) {
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


TokenList TokenProcess::parseTokens(const TokenList& source) {
	TokenList res;

	for (const Token& token : source)
		switch (token.getType()) {
		case COLOR: {
			const std::string parsed = ColorParser(token.getSub()).parse()->toString();
			res.push_back(Token(LITERAL, parsed, new LiteralValue(parsed), {}, token.getIndex()));
			break;
		}

		case EXPRESSION: {
			Expr* const parsed = ExprParser(token.getSub(), *System::input()).parse();
			LiteralValue* const interpreted = ExprInterpreter().interpret(parsed);
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


TokenList TokenProcess::expandRetCommands(const TokenList& source) {
	TokenList res;

	for (size_t i = 0; i < source.size(); i++) {
		const Token token = source[i];

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


inline Token TokenProcess::getRetCommandReturn(const TokenList& source, size_t& i, bool integrate) {
	RetCommandBase* retCmd = nullptr;
	LiteralValue* ret = nullptr;
	TokenList list;
	bool hasExplicitList = false;

	argsFromList(source, i, list);

	// don't encapsulate in RETCOMMANDS
	ArgList args = CmdUtil::getArgs(list, false, true, &hasExplicitList);

	if (integrate)
		insertIntegrate(args, source[i - 1].getLiteral());

	// no flags support in RETCOMMANDS
	retCmd = CmdUtil::getRetCommand(source[i].getLexical().substr(1), args, {});

	if (!retCmd)
		throw SystemException(CommandError, "Unknown command: " + clr(source[i].getLexical(), __clr_command->toString()));

	ret = retCmd->exec();

	if (hasExplicitList) i++;

	return Token(TypeUtil::getLitTokenEnum(ret), "", ret, {}, source[i].getIndex());
}