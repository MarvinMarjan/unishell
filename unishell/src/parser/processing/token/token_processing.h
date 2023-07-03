#pragma once

#include "../../../color/parser/color_parser.h"
#include "../../../expression/parser/expr_parser.h"
#include "../../../expression/interpreter/expr_interpreter.h"
#include "../../../commands/cmdcore/args.h"

class TokenProcess
{
public:
	// process all tokens
	static TokenList process(TokenList source) {
		source = generateBlocks(source);

		source = expandTokens(source);
		source = reduceTokens(source);
		source = parseTokens(source);
		
		source = generateLists(source);
		source = generateObjects(source);
		source = subToLiteral(source);
		source = expandRetCommands(source);

		source = processKeywords(source);

		return source;
	}

private:
	static TokenList processKeywords(const TokenList& source);

	// execute a RETCOMMAND and replace it by
	// the returned value
	static TokenList expandRetCommands(const TokenList& source);

	// gets the return value of a RETCOMMAND
	static Token getRetCommandReturn(const TokenList& source, size_t& i, bool integrate = false);

	// if the Token after a RETCOMMAND is a LIST, then
	// interpret it as arguments and return a list containing
	// the RETCOMMAND and LIST, respectively
	constexpr static void argsFromList(const TokenList& source, size_t i, TokenList& list) {
		if (i + 1 < source.size() && source[i + 1].getType() == LIST)
			for (size_t o = i; o < i + 2; o++)
				list.push_back(source[o]);
	}

	constexpr static void insertIntegrate(ArgList& args, lit::LiteralValue* integrateLiteral) {
		args.insert(args.begin() + 0, integrateLiteral);
	}



	// transforms LIST tokens with sub tokens into
	// LIST tokens with literals instead
	static TokenList subToLiteral(const TokenList& source);

	// returns true if "token" has a literal
	static bool addIfHasLiteral(TokenList& list, const Token& token) noexcept {
		if (token.getLiteral())
			list.push_back(token);

		return token.getLiteral();
	}

	// parse tokens that can be parsed. if token
	// can be interpreted, interpret it
	static TokenList parseTokens(const TokenList& source);


	// reduce tokens that can be reduced into a 
	// higher-level token like EXPRESSION
	static TokenList reduceTokens(TokenList source) {
		source = generateExpressions(source);
		source = generateColorTokens(source);

		return source;
	}
	

	// expands (replace) tokens that can be expanded by they
	// corresponding value like IDENTIFIER
	static TokenList expandTokens(const TokenList& source);


	// receive a token that represents a symbol and return a new token
	// containing the value inside that symbol. if the identifier doesn't
	// exists, a exception
	static Token assignIdentifierToken(Token token) {
		const Identifier respectiveId = *System::getEnvId(token.lexical.substr(1), (int)token.index);
		lit::LiteralValue* idValue = respectiveId.getValue();

		token.lexical = litToStr(idValue);
		token.lit = idValue;
		token.type = lit::typeToTokenEnum(respectiveId.getType());

		return token;
	}

	// get tokens inside lchar and rchar and add to res
	// a token of resToken type
	static void getInside(TokenList& res, const TokenList& source, const TokenEnum lchar, const TokenEnum rchar, 
		const TokenEnum resToken, const std::string& errMsg, const bool processSub = false);

	static void checkIndex(const TokenList& source, size_t& i, const unsigned short aux, const std::string& errMsg) {
		if (i + 1 >= source.size() && aux)
			throw new TokenProcessingErr(errMsg, ExceptionRef(UNISHLL_USER_INPUT, source[i]));
		else
			i++;
	}

	constexpr static void checkLRChar(const TokenList& source, size_t& i, unsigned short& aux, const TokenEnum lchar, const TokenEnum rchar) noexcept {
		if (source[i].getType() == lchar) aux++;
		if (source[i].getType() == rchar) aux--;
	}


	
	// identify expressions and generate a EXPRESSION type conataining
	// the expression body
	static TokenList generateExpressions(const TokenList& source) {
		TokenList res;

		getInside(res, source, LPAREN, RPAREN, EXPRESSION, "Unterminated expression", true);

		return res;
	}

	static TokenList generateBlocks(const TokenList& source) {
		TokenList res;

		getInside(res, source, BEGIN, END, BLOCK, "Unterminated block");

		return res;
	}

	// identify lists and generate a LIST type containing
	// the list values
	static TokenList generateLists(const TokenList& source) {
		TokenList res;

		getInside(res, source, LBRACKET, RBRACKET, LIST, "Unterminated list");

		return res;
	}

	// identify objects and generate a OBJECT type containing
	// the pairs inside it
	static TokenList generateObjects(const TokenList& source) {
		TokenList res;

		getInside(res, source, LBRACE, RBRACE, OBJECT, "Unterminated object");

		return res;
	}
	
	// identify color syntax and generate a COLOR containing
	// the color syntax
	static TokenList generateColorTokens(const TokenList& source);

	static void consume(const TokenList& source, const TokenEnum delimiter, size_t& i, const std::string& errMsg) {
		while (source[i].getType() != delimiter) {
			if (i + 1 >= source.size())
				throw new TokenProcessingErr(errMsg, ExceptionRef(UNISHLL_USER_INPUT, __userInput->size() - 1));
			else
				i++;
		}
	}
};