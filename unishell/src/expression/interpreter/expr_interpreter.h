#pragma once

#include "../expr.h"
#include "../../data/litvalue/litformat.h"
#include "../../data/litvalue/checking.h"
#include "../../system/system.h"

class ExprInterpreter : public ExprVisitor
{
public:
	lit::LiteralValue* interpret(Expr* expr) {
		return evaluate(expr);
	}

private:
	lit::LiteralValue* visitLiteralExpr(LiteralExpr* expr) override;
	lit::LiteralValue* visitGroup(Group* expr) override;
	lit::LiteralValue* visitUnary(Unary* expr) override;
	lit::LiteralValue* visitBinary(Binary* expr) override;


	lit::LiteralValue* evaluate(Expr* expr) {
		lit::LiteralValue* result = expr->accept(this);
		expr->~Expr();

		return result;
	}
	
	bool isTruthy(lit::LiteralValue* value) {
		if (!value) return false;
		if (value->type() == lit::LitType::Bool) return asBool(value);

		return true;
	}

	bool isEqual(lit::LiteralValue* a, lit::LiteralValue* b, const bool strict = false) {
		if (!a && !b) return true;
		if (!a) return false;

		if (!strict)
			return (litToStr(a) == litToStr(b));
		
		// strict equality
		if (a->type() != b->type()) return false;
		
		return (litToStr(a) == litToStr(b));
	}



	void checkLiteralType(lit::LiteralValue* value, const std::vector<lit::LiteralValue::Type>& expectedTypes, const Token& token);

	void checkLiteralType(const std::vector<lit::LiteralValue*>& vals, const std::vector<lit::LiteralValue::Type>& expectedTypes, const Token& token) {
		for (lit::LiteralValue* value : vals)
			checkLiteralType(value, expectedTypes, token);
	}
};