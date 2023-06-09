#pragma once

#include "../../utilities/typeUtil.h"

#include "expr.h"


class ExprASTPrinter : public ExprVisitor
{
public:
	inline LiteralValue* print(Expr* expr) {
		return expr->accept(this);
	}

private:
	LiteralValue* visitBinary(Binary* expr) override {
		return parenthesize(expr->op.getLexical(), { expr->left, expr->right });
	}

	LiteralValue* visitUnary(Unary* expr) override {
		return parenthesize(expr->op.getLexical(), { expr->expr });
	}

	LiteralValue* visitGroup(Group* expr) override {
		return parenthesize("group", { expr->expression });
	}

	LiteralValue* visitLiteralExpr(LiteralExpr* expr) override {
		if (!expr->value) return new LiteralValue(std::string("null"));
		return new LiteralValue(litToStr(expr->value));
	}


	inline LiteralValue* parenthesize(const std::string& name, const std::vector<Expr*>& exprs) {
		std::stringstream builder;

		builder << "(" << name;

		for (Expr* expr : exprs) {
			builder << " ";
			builder << std::get<std::string>(*expr->accept(this));
		}

		builder << ")";

		return new LiteralValue(builder.str());
	}
};