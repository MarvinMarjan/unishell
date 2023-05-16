#pragma once

#include "type.h"
#include "../instream/token.h"

class Binary;
class Unary;
class Group;
class LiteralExpr;

class ExprVisitor
{
public:
	virtual LiteralValue* visitBinary(Binary*) = 0;
	virtual LiteralValue* visitUnary(Unary*) = 0;
	virtual LiteralValue* visitGroup(Group*) = 0;
	virtual LiteralValue* visitLiteralExpr(LiteralExpr*) = 0;
};

class Expr {
public:
	virtual LiteralValue* accept(ExprVisitor*) = 0;
};

class Binary : public Expr
{
public:
	friend class ExprASTPrinter;

	Binary(Expr* left, Token op, Expr* right) : left(left), op(op), right(right) {}

	LiteralValue* accept(ExprVisitor* v) override {
		return v->visitBinary(this);
	}

private:
	Expr* left;
	Token op;
	Expr* right;
};

class Unary : public Expr
{
public:
	friend class ExprASTPrinter;

	Unary(Token op, Expr* expr) : op(op), expr(expr) {}

	LiteralValue* accept(ExprVisitor* v) override {
		return v->visitUnary(this);
	}

private:
	Token op;
	Expr* expr;
};

class Group : public Expr
{
public:
	friend class ExprASTPrinter;

	Group(Expr* expression) : expression(expression) {}

	LiteralValue* accept(ExprVisitor* v) override {
		return v->visitGroup(this);
	}

private:
	Expr* expression;
};

class LiteralExpr : public Expr
{
public:
	friend class ExprASTPrinter;

	LiteralExpr(LiteralValue* value) : value(value) {}

	LiteralValue* accept(ExprVisitor* v) override {
		return v->visitLiteralExpr(this);
	}

private:
	LiteralValue* value;
};
