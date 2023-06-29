#include "type.h"

lit::LiteralValue* lit::getListFromTokenList(const TokenList& source)
{
	LiteralValue* const lit = new LiteralValue(LitList());
	
	for (const Token& token : source)
		asList(lit).push_back(token.getLiteral());

	return lit;
}


lit::LiteralValue* lit::getObjFromTokenList(const TokenList& source)
{
	LiteralValue* const lit = new LiteralValue(LitObject());
	LiteralValue* aux;

	for (const Token& token : source) {
		if (token.getType() != LIST) continue;
		if (!token.getLiteral()) continue;
		if (asList(token.getLiteral()).size() < 2) continue;

		aux = token.getLiteral();

		if (LiteralValue::typeof(asList(aux)[0]) != LitType::Literal)
			throw new TokenProcessingErr("Literal type expected for property name", ExceptionRef(*__userInput, token));

		asObj(lit).insert({ asStr(asList(aux)[0]), asList(aux)[1] });
	}

	return lit;
}
