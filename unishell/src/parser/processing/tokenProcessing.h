#pragma once

#include "../instream/token.h"
#include "../../system/system.h"

#include "../color/colorParser.h"
#include "../expression/exprParser.h"
#include "../expression/exprInterpreter.h"

#include "../../utilities/cmdUtil.h"

class TokenProcess
{
public:
	// process all tokens
	static inline TokenList process(TokenList source) {
		source = expandTokens(source);
		source = reduceTokens(source);
		source = parseTokens(source);
		
		source = generateLists(source);
		source = generateObjects(source);
		source = subToLiteral(source);
		source = expandRetCommands(source);

		return source;
	}

private:
	// execute a RETCOMMAND and replace it by
	// the returned value
	static TokenList expandRetCommands(const TokenList& source);

	// gets the return value of a RETCOMMAND
	static Token getRetCommandReturn(const TokenList& source, size_t& i, bool integrate = false);

	// if the Token after a RETCOMMAND is a LIST, then
	// interpret it as arguments and return a list containing
	// the RETCOMMAND and LIST, respectively
	static inline void argsFromList(const TokenList& source, size_t i, TokenList& list) {
		if (i + 1 < source.size() && source[i + 1].getType() == LIST)
			for (size_t o = i; o < i + 2; o++)
				list.push_back(source[o]);
	}

	static inline void insertIntegrate(ArgList& args, LiteralValue* integrateLiteral) {
		args.insert(args.begin() + 0, integrateLiteral);
	}



	// transforms LIST tokens with sub tokens into
	// LIST tokens with literals instead
	static inline TokenList subToLiteral(TokenList source) {
		TokenList res;

		for (Token token : source)
			switch (token.getType()) {
			case LIST: {
				if (token.getLiteral()) {
					res.push_back(token);
					break;
				}

				TokenList parsed = process(token.getSub());
				res.push_back(Token(LIST, "", getListFromTokenList(parsed), {}, token.getIndex()));
				break;
			}

			case OBJECT: {
				if (token.getLiteral()) {
					res.push_back(token);
					break;
				}

				TokenList parsed = process(token.getSub());
				res.push_back(Token(OBJECT, "", getObjFromTokenList(parsed), {}, token.getIndex()));
				break;
			}

			default:
				res.push_back(token);
			}

		return res;
	}

	// parse tokens that can be parsed. if token
	// can be interpreted, interpret it
	static TokenList parseTokens(const TokenList& source);


	// reduce tokens that can be reduced into a 
	// higher-level token like EXPRESSION
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
			switch (token.getType()) {
			case IDENTIFIER:
				res.push_back(assignIdentifierToken(token));
				break;

			default:
				res.push_back(token);
			}
		}

		return res;
	}

	// receive a token that represents a symbol and return a new token
	// containing the value inside that symbol. if the identifier doesn't
	// exists, a exception
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
	static void getInside(TokenList& res, const TokenList& source, TokenEnum lchar, TokenEnum rchar, TokenEnum resToken, const std::string& errMsg, bool processSub = false);

	static inline void checkIndex(TokenList source, size_t& i, unsigned short aux, const std::string& errMsg) {
		if (i + 1 >= source.size() && aux)
			throw SystemException(TokenProcessingError, errMsg, ExceptionRef(USER_INPUT, source[i].getIndex()));
		else
			i++;
	}

	static inline void checkLRChar(TokenList source, size_t& i, unsigned short& aux, TokenEnum lchar, TokenEnum rchar) noexcept {
		if (source[i].getType() == lchar) aux++;
		if (source[i].getType() == rchar) aux--;
	}


	
	// identify expressions and generate a EXPRESSION type conataining
	// the expression body
	static inline TokenList generateExpressions(TokenList source) {
		TokenList res;

		getInside(res, source, LPAREN, RPAREN, EXPRESSION, "Unterminated expression", true);

		return res;
	}

	// identify lists and generate a LIST type containing
	// the list values
	static inline TokenList generateLists(TokenList source) {
		TokenList res;

		getInside(res, source, LBRACKET, RBRACKET, LIST, "Unterminated list");

		return res;
	}

	static inline TokenList generateObjects(TokenList source) {
		TokenList res;

		getInside(res, source, LBRACE, RBRACE, OBJECT, "Unterminated object");

		return res;
	}
	
	// identify color syntax and generate a COLOR containing
	// the color syntax
	static TokenList generateColorTokens(const TokenList& source);

	static inline void consume(TokenList source, TokenEnum delimiter, size_t& i, const std::string& errMsg) {
		while (source[i].getType() != delimiter) {
			if (i + 1 >= source.size())
				throw SystemException(TokenProcessingError, errMsg, ExceptionRef(USER_INPUT, System::input()->size() - 1));
			else
				i++;
		}
	}
};