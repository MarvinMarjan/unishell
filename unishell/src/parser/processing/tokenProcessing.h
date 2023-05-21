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
		//source = reviewTokens(source);

		source = generateLists(source); // must be the last stage

		return source;
	}

private:
	/*static TokenList reviewTokens(TokenList source) {
		TokenList res;

		for (Token token : source) {
			if (token.getType() == NULLVAL)
				res.push_back(litToStr(token.getLiteral()));
			else
				res.push_back(token);
		}

		return res;
	}*/

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
		LiteralValue* idValue = respectiveId.getValue();

		token.lexical = litToStr(idValue);
		token.lit = idValue;
		token.type = TypeUtil::getTypeAsTokenEnum(respectiveId.getType());

		return token;
	}

	// get tokens inside lchar and rchar and add to res
	// a token of resToken type
	static inline void getInside(TokenList& res, TokenList source, TokenEnum lchar, TokenEnum rchar, TokenEnum resToken, const std::string& errMsg) {
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

				res.push_back(Token(resToken, "", nullptr, TokenList(source.begin() + start + 1, source.begin() + end), res.size() - 1));
			}

			else res.push_back(source[i]);
		}
	}

	static inline void checkIndex(TokenList source, size_t& i, unsigned short aux, const std::string& errMsg) {
		if (i + 1 >= source.size() && aux)
			throw SystemException(TokenProcessingError, errMsg, ExceptionRef(USER_INPUT, source[i].getIndex()));
		else
			i++;
	}

	static inline void checkLRChar(TokenList source, size_t& i, unsigned short& aux, TokenEnum lchar, TokenEnum rchar) {
		if (source[i].getType() == lchar) aux++;
		if (source[i].getType() == rchar) aux--;
	}


	
	// identify expressions and generate a EXPRESSION type conataining
	// the expression body
	static TokenList generateExpressions(TokenList source) {
		TokenList res;

		getInside(res, source, LPAREN, RPAREN, EXPRESSION, "Unterminated expression");

		return res;
	}

	// identify lists and generate a LIST type containing
	// the list values
	static TokenList generateLists(TokenList source) {
		TokenList res;

		getInside(res, source, LBRACE, RBRACE, LIST, "Unterminated list");

		return res;
	}
	
	// identify color syntax and generate a COLOR containing
	// the color syntax
	static TokenList generateColorTokens(TokenList source);

	static inline void consume(TokenList source, TokenEnum delimiter, size_t& i, const std::string& errMsg) {
		while (source[i].getType() != delimiter) {
			if (i + 1 >= source.size())
				throw SystemException(TokenProcessingError, errMsg, ExceptionRef(USER_INPUT, System::input()->size() - 1));
			else
				i++;
		}
	}
};