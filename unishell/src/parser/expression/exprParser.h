#pragma once

#include "expr.h"

#include "../instream/token.h"

#include "../../system/systemException.h"

class ExprParser
{
public:
	ExprParser(const TokenList& tokens, const std::string& rawSource) :
		tokens(tokens), rawSource(rawSource)
	{
		current = 0;
	}

	inline Expr* parse() {
		return expression();
	}

private:
	inline Expr* expression() {
		return logicOperator();
	}

	inline Expr* logicOperator() {
		Expr* expr = assignment();

		while (match({ AND, OR })) {
			const Token op = prev();
			Expr* right = assignment();
			expr = new Binary(expr, op, right);
		}

		if (match({ NUMBER, LITERAL, BOOLEANVAL, LIST, OBJECT, LPAREN }))
			throw SystemException(ExprParserError, "Operator expected", ExceptionRef(rawSource, prev().getIndex()));

		return expr;
	}

	inline Expr* assignment() {
		Expr* expr = equality();
		
		while (match({ EQUAL })) {
			const Token op = prev();
			Expr* right = equality();
			expr = new Binary(expr, op, right);
		}

		return expr;
	}

	inline Expr* equality() {
		Expr* expr = comparison();

		while (match({ EQUAL_EQUAL_EQUAL, EQUAL_EQUAL, BANG_EQUAL })) {
			const Token op = prev();
			Expr* right = comparison();
			expr = new Binary(expr, op, right);
		}

		return expr;
	}

	inline Expr* comparison() {
		Expr* expr = term();

		while (match({ GREATER, LESS, GREATER_EQUAL, LESS_EQUAL })) {
			const Token op = prev();
			Expr* right = term();
			expr = new Binary(expr, op, right);
		}

		return expr;
	}

	inline Expr* term() {
		Expr* expr = factor();

		while (match({ PLUS, MINUS })) {
			const Token op = prev();
			Expr* right = factor();
			expr = new Binary(expr, op, right);
		}

		return expr;
	}

	inline Expr* factor() {
		Expr* expr = unary();

		while (match({ STAR, SLASH })) {
			const Token op = prev();
			Expr* right = unary();
			expr = new Binary(expr, op, right);
		}

		return expr;
	}

	inline Expr* unary() {
		if (match({ BANG, MINUS })) {
			const Token op = prev();
			Expr* expr = unary();
			return new Unary(op, expr);
		}

		return primary();
	}

	inline Expr* primary() {
		if (match({ NUMBER, LITERAL, BOOLEANVAL, LIST, OBJECT }))
			return new LiteralExpr(prev().getLiteral());

		if (match({ NULLVAL }))
			return new LiteralExpr(nullptr);

		if (match({ LPAREN })) {
			Expr* expr = expression();
			advance();
			return new Group(expr);
		}

		if (!tokens.size())
			return new LiteralExpr(nullptr);

		throw SystemException(ExprParserError, "Expression expected", ExceptionRef(rawSource, prev().getIndex()));
	}


	inline bool match(const std::vector<TokenEnum>& tokenTypes) {
		for (TokenEnum type : tokenTypes) {
			if (check(type)) {
				advance();
				return true;
			}
		}

		return false;
	}


	inline Token consume(TokenEnum type, const std::string& msg) {
		if (check(type))
			return advance();

		throw SystemException(ExprParserError, msg);
	}


	inline bool check(TokenEnum type) {
		if (isAtEnd())
			return false;

		return (peek().getType() == type);
	}

	inline Token advance() noexcept {
		if (!isAtEnd())
			current++;

		return prev();
	}

	inline Token peek() const noexcept {
		return tokens[current];
	}

	inline Token prev() const noexcept {
		if (!current) 
			return tokens[(size_t)current];

		return tokens[(size_t)current - 1];
	}

	constexpr inline bool isAtEnd() const noexcept {
		return ((size_t)current >= tokens.size());
	}

	std::string rawSource;
	TokenList tokens;
	unsigned int current;
};
