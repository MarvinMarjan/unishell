#pragma once

#include "../instream/token.h"
#include "../../system/system.h"

#include "../color/colorParser.h"
#include "../expression/exprParser.h"
#include "../expression/exprInterpreter.h"

#include "../../commands/cmdsDef.h"

class TokenProcess
{
public:
	// process all tokens
	static inline TokenList process(TokenList source) {
		source = expandTokens(source);
		source = reduceTokens(source);
		source = parseTokens(source);
		
		source = generateLists(source);
		source = listsToLiteral(source);
		source = expandRetCommands(source);

		return source;
	}

private:
	// execute a RETCOMMAND and replace it by
	// the returned value
	static inline TokenList expandRetCommands(TokenList source) {
		TokenList res;
		
		for (size_t i = 0; i < source.size(); i++) {
			Token token = source[i];

			switch (token.getType()) {
			case RETCOMMAND:
				res.push_back(getRetCommandReturn(source, i));
				break;

			default:
				res.push_back(token);
			}
		}

		return res;
	}

	// transforms LIST tokens with sub tokens into
	// LIST tokens with literals instead
	static inline TokenList listsToLiteral(TokenList source) {
		TokenList res;

		for (Token token : source)
			switch (token.getType()) {
			case LIST: {
				TokenList parsed = process(token.getSub());
				res.push_back(Token(LIST, "", getFromTokenList(parsed), {}, token.getIndex()));
				break;
			}

			default:
				res.push_back(token);
			}

		return res;
	}

	// parse tokens that can be parsed. if token
	// can be interpreted, interpret it
	static TokenList parseTokens(TokenList source);


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
	// exists, throw a exception
	static inline Token assignIdentifierToken(Token token) {
		Identifier respectiveId = *System::getEnvId(token.lexical.substr(1), (int)token.index);
		LiteralValue* idValue = respectiveId.getValue();

		token.lexical = litToStr(idValue);
		token.lit = idValue;
		token.type = TypeUtil::getTypeAsTokenEnum(respectiveId.getType());

		return token;
	}

	// gets the return value of a RETCOMMAND
	static inline Token getRetCommandReturn(TokenList source, size_t& i) {
		RetCommandBase* retCmd = nullptr;
		LiteralValue* ret = nullptr;
		TokenList list;

		if (i + 1 < source.size() && source[i + 1].getType() == LIST)
			list = TokenList(source.begin() + i, source.begin() + i + 2);

		// don't encapsulate args in RETCOMMANDS
		retCmd = getRetCommand(source[i].getLexical().substr(1), getArgs(list, false));

		if (!retCmd)
			throw SystemException(CommandError, "Unknown command: " + qtd(source[i].getLexical()));

		ret = retCmd->exec();

		if (list.size()) i++;

		return Token(TypeUtil::getTypeAsTokenEnum(getValueActiveType(ret)), litToStr(ret), ret, {}, source[i].getIndex());
	}

	// get tokens inside lchar and rchar and add to res
	// a token of resToken type
	static inline void getInside(TokenList& res, TokenList source, TokenEnum lchar, TokenEnum rchar, TokenEnum resToken, const std::string& errMsg, bool processSub = false) noexcept {
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

				res.push_back(Token(resToken, "", nullptr, sub, res.size() - 1));
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

	static inline void checkLRChar(TokenList source, size_t& i, unsigned short& aux, TokenEnum lchar, TokenEnum rchar) noexcept {
		if (source[i].getType() == lchar) aux++;
		if (source[i].getType() == rchar) aux--;
	}


	
	// identify expressions and generate a EXPRESSION type conataining
	// the expression body
	static TokenList generateExpressions(TokenList source) {
		TokenList res;

		getInside(res, source, LPAREN, RPAREN, EXPRESSION, "Unterminated expression", true);

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