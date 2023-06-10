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
	friend class ExprInterpreter;

	Binary(Expr* left, Token op, Expr* right) : left(left), op(op), right(right) {}

	constexpr LiteralValue* accept(ExprVisitor* v) override {
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
	friend class ExprInterpreter;

	Unary(Token op, Expr* expr) : op(op), expr(expr) {}

	constexpr LiteralValue* accept(ExprVisitor* v) override {
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
	friend class ExprInterpreter;

	Group(Expr* expression) : expression(expression) {}

	constexpr LiteralValue* accept(ExprVisitor* v) override {
		return v->visitGroup(this);
	}

private:
	Expr* expression;
};

class LiteralExpr : public Expr
{
public:
	friend class ExprASTPrinter;
	friend class ExprInterpreter;

	LiteralExpr(LiteralValue* value) : value(value) {}

	constexpr LiteralValue* accept(ExprVisitor* v) override {
		return v->visitLiteralExpr(this);
	}

private:
	LiteralValue* value;
};
