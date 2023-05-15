#pragma once

#include "expr.h"
#include "token.h"

#include "../../system/systemException.h"

class ExprParser
{
public:
	ExprParser(ExprTokenList tokens) : tokens(tokens) {
		current = 0;
	}

	inline Expr* parse() {
		return expression();
	}

private:
	inline Expr* expression() {
		return equality();
	}

	inline Expr* equality() {
		Expr* expr = comparison();

		while (match({ EQUAL_EQUAL, BANG_EQUAL })) {
			ExprToken op = prev();
			Expr* right = comparison();
			expr = new Binary(expr, op, right);
		}

		return expr;
	}

	inline Expr* comparison() {
		Expr* expr = term();

		while (match({ GREATER, LESS, GREATER_EQUAL, LESS_EQUAL })) {
			ExprToken op = prev();
			Expr* right = term();
			expr = new Binary(expr, op, right);
		}

		return expr;
	}

	inline Expr* term() {
		Expr* expr = factor();

		while (match({ PLUS, MINUS })) {
			ExprToken op = prev();
			Expr* right = factor();
			expr = new Binary(expr, op, right);
		}

		return expr;
	}

	inline Expr* factor() {
		Expr* expr = unary();

		while (match({ STAR, SLASH })) {
			ExprToken op = prev();
			Expr* right = unary();
			expr = new Binary(expr, op, right);
		}

		return expr;
	}

	inline Expr* unary() {
		if (match({ BANG, MINUS })) {
			ExprToken op = prev();
			Expr* expr = unary();
			return new Unary(op, expr);
		}

		return primary();
	}

	inline Expr* primary() {
		if (match({ NUMBER })) return new LiteralExpr(prev().getLiteral());

		if (match({ LPAREN })) {
			Expr* expr = expression();
			advance();
			return new Group(expr);
		}

		// TODO: improve this:
		throw SystemException(ExprParserError, "Expression expected", ExceptionRef(prev().getLexical()));
	}


	inline bool match(std::vector<ExprTokenType> tokenTypes) {
		for (ExprTokenType type : tokenTypes) {
			if (check(type)) {
				advance();
				return true;
			}
		}

		return false;
	}


	inline ExprToken consume(ExprTokenType type, const std::string& msg) {
		if (check(type)) return advance();

		throw SystemException(ExprParserError, msg);
	}


	inline bool check(ExprTokenType type) {
		if (isAtEnd()) return false;
		return (peek().getType() == type);
	}

	inline ExprToken advance() noexcept {
		if (!isAtEnd()) current++;
		return prev();
	}

	inline ExprToken peek() const noexcept {
		return tokens[current];
	}

	inline ExprToken prev() const noexcept {
		return tokens[(size_t)current - 1];
	}

	inline bool isAtEnd() const noexcept {
		return ((size_t)current >= tokens.size());
	}

	ExprTokenList tokens;
	unsigned int current;
};
