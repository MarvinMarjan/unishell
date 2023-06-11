#pragma once

#include "../../utilities/typeUtil.h"

#include "../expr.h"


class ExprASTPrinter : public ExprVisitor
{
public:
	constexpr LiteralValue* print(Expr* expr) {
		return expr->accept(this);
	}

private:
	constexpr LiteralValue* visitBinary(Binary* expr) override {
		return parenthesize(expr->op.getLexical(), { expr->left, expr->right });
	}

	constexpr LiteralValue* visitUnary(Unary* expr) override {
		return parenthesize(expr->op.getLexical(), { expr->expr });
	}

	constexpr LiteralValue* visitGroup(Group* expr) override {
		return parenthesize("group", { expr->expression });
	}

	constexpr LiteralValue* visitLiteralExpr(LiteralExpr* expr) override {
		if (!expr->value) return new LiteralValue(std::string("null"));
		return new LiteralValue(litToStr(expr->value));
	}


	constexpr LiteralValue* parenthesize(const std::string& name, const std::vector<Expr*>& exprs) {
		std::string builder;

		builder += "(" + name;

		for (Expr* expr : exprs) {
			builder += " ";
			builder += std::get<std::string>(*expr->accept(this));
		}

		builder += ")";

		return lit(builder);
	}
};