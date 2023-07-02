#pragma once

#include "../data/litvalue/type.h"

class Binary;
class Unary;
class Group;
class LiteralExpr;

class ExprVisitor
{
public:
	virtual lit::LiteralValue* visitBinary(Binary*) = 0;
	virtual lit::LiteralValue* visitUnary(Unary*) = 0;
	virtual lit::LiteralValue* visitGroup(Group*) = 0;
	virtual lit::LiteralValue* visitLiteralExpr(LiteralExpr*) = 0;
};

class Expr {
public:
	virtual ~Expr() = default;

	virtual lit::LiteralValue* accept(ExprVisitor*) = 0;
};

class Binary : public Expr
{
public:
	friend class ExprASTPrinter;
	friend class ExprInterpreter;

	Binary(Expr* left, const Token& op, Expr* right) : left(left), op(op), right(right) {}
	
	~Binary() {
		if (left) {
			left->~Expr();
			delete left;
			left = nullptr;
		}

		if (right) {
			right->~Expr();
			delete right;
			right = nullptr;
		}
	}

	lit::LiteralValue* accept(ExprVisitor* v) override {
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

	Unary(const Token& op, Expr* expr) : op(op), expr(expr) {}
	~Unary() {
		if (expr) {
			expr->~Expr();
			delete expr;
			expr = nullptr;
		}
	}

	lit::LiteralValue* accept(ExprVisitor* v) override {
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
	~Group() {
		if (expression) {
			expression->~Expr();
			delete expression;
			expression = nullptr;
		}
	}

	lit::LiteralValue* accept(ExprVisitor* v) override {
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

	LiteralExpr(lit::LiteralValue* value) : value(value) {}

	~LiteralExpr() {}

	lit::LiteralValue* accept(ExprVisitor* v) override {
		return v->visitLiteralExpr(this);
	}

private:
	lit::LiteralValue* value;
};
