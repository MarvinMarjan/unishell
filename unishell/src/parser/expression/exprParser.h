#pragma once

#include "expr.h"

#include "../instream/token.h"

#include "../../system/systemException.h"

class ExprParser
{
public:
	ExprParser(TokenList tokens) : tokens(tokens) {
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
		Expr* expr = equality();

		while (match({ AND, OR })) {
			Token op = prev();
			Expr* right = equality();
			expr = new Binary(expr, op, right);
		}

		return expr;
	}

	inline Expr* equality() {
		Expr* expr = comparison();

		while (match({ EQUAL_EQUAL, BANG_EQUAL })) {
			Token op = prev();
			Expr* right = comparison();
			expr = new Binary(expr, op, right);
		}

		return expr;
	}

	inline Expr* comparison() {
		Expr* expr = term();

		while (match({ GREATER, LESS, GREATER_EQUAL, LESS_EQUAL })) {
			Token op = prev();
			Expr* right = term();
			expr = new Binary(expr, op, right);
		}

		return expr;
	}

	inline Expr* term() {
		Expr* expr = factor();

		while (match({ PLUS, MINUS })) {
			Token op = prev();
			Expr* right = factor();
			expr = new Binary(expr, op, right);
		}

		return expr;
	}

	inline Expr* factor() {
		Expr* expr = unary();

		while (match({ STAR, SLASH })) {
			Token op = prev();
			Expr* right = unary();
			expr = new Binary(expr, op, right);
		}

		return expr;
	}

	inline Expr* unary() {
		if (match({ BANG, MINUS })) {
			Token op = prev();
			Expr* expr = unary();
			return new Unary(op, expr);
		}

		return primary();
	}

	inline Expr* primary() {
		if (match({ NUMBER, LITERAL, BOOLEANVAL })) return new LiteralExpr(prev().getLiteral());

		if (match({ LPAREN })) {
			Expr* expr = expression();
			advance();
			return new Group(expr);
		}

		// TODO: improve this:
		throw SystemException(ExprParserError, "Expression expected", ExceptionRef(prev().getLexical()));
	}


	inline bool match(std::vector<TokenEnum> tokenTypes) {
		for (TokenEnum type : tokenTypes) {
			if (check(type)) {
				advance();
				return true;
			}
		}

		return false;
	}


	inline Token consume(TokenEnum type, const std::string& msg) {
		if (check(type)) return advance();

		throw SystemException(ExprParserError, msg);
	}


	inline bool check(TokenEnum type) {
		if (isAtEnd()) return false;
		return (peek().getType() == type);
	}

	inline Token advance() noexcept {
		if (!isAtEnd()) current++;
		return prev();
	}

	inline Token peek() const noexcept {
		return tokens[current];
	}

	inline Token prev() const noexcept {
		return tokens[(size_t)current - 1];
	}

	inline bool isAtEnd() const noexcept {
		return ((size_t)current >= tokens.size());
	}

	TokenList tokens;
	unsigned int current;
};
