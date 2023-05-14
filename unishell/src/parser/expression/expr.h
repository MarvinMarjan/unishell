#pragma once

#include "type.h"
#include "../instream/token.h"

class Expr {};

class Binary : public Expr
{
public:
	Binary(Expr* left, InputToken token, Expr* right) : left(left), token(token), right(right) {}

private:
	Expr* left;
	InputToken token;
	Expr* right
};

class Group : public Expr
{
public:
	Group(Expr* expression) : expression(expression) {}

private:
	Expr* expression;
};

class LiteralExpr : public Expr
{
public:
	LiteralExpr(LiteralValue value) : value(value) {}

private:
	LiteralValue value;
};
