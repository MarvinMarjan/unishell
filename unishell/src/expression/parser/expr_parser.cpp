#include "expr_parser.h"


Expr* ExprParser::expression() {
	return logicOperator();
}


Expr* ExprParser::logicOperator() {
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


Expr* ExprParser::assignment() {
	Expr* expr = equality();

	while (match({ EQUAL })) {
		const Token op = prev();
		Expr* right = equality();
		expr = new Binary(expr, op, right);
	}

	return expr;
}


Expr* ExprParser::equality() {
	Expr* expr = comparison();

	while (match({ EQUAL_EQUAL_EQUAL, EQUAL_EQUAL, BANG_EQUAL })) {
		const Token op = prev();
		Expr* right = comparison();
		expr = new Binary(expr, op, right);
	}

	return expr;
}


Expr* ExprParser::comparison() {
	Expr* expr = term();

	while (match({ GREATER, LESS, GREATER_EQUAL, LESS_EQUAL })) {
		const Token op = prev();
		Expr* right = term();
		expr = new Binary(expr, op, right);
	}

	return expr;
}


Expr* ExprParser::term() {
	Expr* expr = factor();

	while (match({ PLUS, MINUS })) {
		const Token op = prev();
		Expr* right = factor();
		expr = new Binary(expr, op, right);
	}

	return expr;
}


Expr* ExprParser::factor() {
	Expr* expr = unary();

	while (match({ STAR, SLASH })) {
		const Token op = prev();
		Expr* right = unary();
		expr = new Binary(expr, op, right);
	}

	return expr;
}


Expr* ExprParser::unary() {
	if (match({ BANG, MINUS })) {
		const Token op = prev();
		Expr* expr = unary();
		return new Unary(op, expr);
	}

	return primary();
}


Expr* ExprParser::primary() {
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