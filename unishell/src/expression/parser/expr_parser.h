#pragma once

#include "../expr.h"

#include "../../system/exception/system_exception.h"

class ExprParser
{
public:
	ExprParser(const TokenList& tokens, const std::string& rawSource) :
		tokens(tokens), rawSource(rawSource)
	{
		current = 0;
	}

	Expr* parse() {
		return expression();
	}

private:
	Expr* expression();

	Expr* logicOperator();
	Expr* assignment();
	Expr* equality();
	Expr* comparison();
	Expr* term();
	Expr* factor();
	Expr* unary();
	Expr* primary();


	bool match(const std::vector<TokenEnum>& tokenTypes) {
		for (TokenEnum type : tokenTypes) {
			if (check(type)) {
				advance();
				return true;
			}
		}

		return false;
	}


	Token consume(const TokenEnum type, const std::string& msg) {
		if (check(type))
			return advance();

		throw SystemException(ExprParserError, msg);
	}


	bool check(const TokenEnum type) {
		if (isAtEnd())
			return false;

		return (peek().getType() == type);
	}

	Token advance() noexcept {
		if (!isAtEnd())
			current++;

		return prev();
	}

	Token peek() const noexcept {
		return tokens[current];
	}

	Token prev() const noexcept {
		if (!current) 
			return tokens[(size_t)current];

		return tokens[(size_t)current - 1];
	}

	bool isAtEnd() const noexcept {
		return ((size_t)current >= tokens.size());
	}

	std::string rawSource;
	TokenList tokens;
	unsigned int current;
};
