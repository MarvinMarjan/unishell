#pragma once

#include "../expr.h"


class ExprASTPrinter : public ExprVisitor
{
public:
	lit::LiteralValue* print(Expr* expr) {
		return expr->accept(this);
	}

private:
	lit::LiteralValue* visitBinary(Binary* expr) override {
		return parenthesize(expr->op.getLexical(), { expr->left, expr->right });
	}

	lit::LiteralValue* visitUnary(Unary* expr) override {
		return parenthesize(expr->op.getLexical(), { expr->expr });
	}

	lit::LiteralValue* visitGroup(Group* expr) override {
		return parenthesize("group", { expr->expression });
	}

	lit::LiteralValue* visitLiteralExpr(LiteralExpr* expr) override {
		if (!expr->value) return new lit::LiteralValue(std::string("null"));
		return new lit::LiteralValue(litToStr(expr->value));
	}


	lit::LiteralValue* parenthesize(const std::string& name, const std::vector<Expr*>& exprs) {
		std::string builder;

		builder += "(" + name;

		for (Expr* expr : exprs) {
			builder += " ";
			builder += asStr(expr->accept(this));
		}
		
		builder += ")";

		return lit::lit(builder);
	}
};