#pragma once

#include "../instream/token.h"
#include "../../system/system.h"

#include "../color/colorParser.h"
#include "../expression/exprParser.h"
#include "../expression/exprInterpreter.h"

class TokenProcess
{
public:
	// process all tokens
	static inline TokenList process(TokenList source) {
		source = expandTokens(source);
		source = reduceTokens(source);
		source = parseTokens(source);

		return source;
	}

private:
	// parse tokens that can be parsed. if token
	// can be interpreted, interpret it
	static TokenList parseTokens(TokenList source);


	// reduce tokens that can be reduced into a 
	// high-level token like EXPRESSION
	static inline TokenList reduceTokens(TokenList source) {
		source = generateExpressions(source);
		source = generateColorTokens(source);

		return source;
	}


	// indentify expressions and generate a EXPRESSION type conataining
	// the expression body
	static TokenList generateExpressions(TokenList source);

	static inline void checkIndex(TokenList source, size_t& i, unsigned short aux) {
		if (i + 1 >= source.size() && aux)
			throw SystemException(TokenProcessingError, "Unterminated expression", ExceptionRef(*System::input(), source[i].getIndex()));
		else
			i++;
	}

	static inline void checkParen(TokenList source, size_t& i, unsigned short& aux) {
		if (source[i].getType() == LPAREN) aux++;
		if (source[i].getType() == RPAREN) aux--;
	}



	// expands (replace) tokens that can be expanded by they
	// corresponding value like IDENTIFIER
	static inline TokenList expandTokens(TokenList source) {
		TokenList res;

		for (Token token : source) {
			if (token.type == IDENTIFIER)
				token = assignIdentifierToken(token);

			res.push_back(token);
		}

		return res;
	}

	// receive a token that represents a symbol and return a new token
	// containing the value inside that symbol
	static inline Token assignIdentifierToken(Token token) {
		Identifier respectiveId = *System::getEnvId(token.lexical.substr(1), (int)token.index);
		LiteralValue idValue = respectiveId.getValue();

		token.lexical = TypeUtil::literalValueToString(&idValue);
		token.lit = new LiteralValue(idValue);
		token.type = TypeUtil::getTypeAsTokenEnum(respectiveId.getType());

		return token;
	}



	// identify color syntax and generate a COLOR containing
	// the color syntax
	static TokenList generateColorTokens(TokenList source);

	static inline void consume(TokenList source, TokenEnum delimiter, size_t& i, const std::string& errMsg) {
		while (source[i].getType() != delimiter) {
			if (i + 1 >= source.size())
				throw SystemException(TokenProcessingError, errMsg, ExceptionRef(*System::input(), System::input()->size() - 1));
			else
				i++;
		}
	}
};