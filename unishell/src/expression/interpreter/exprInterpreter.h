#pragma once

#include "../expr.h"
#include "../../data/litvalue/litformat.h"
#include "../../data/litvalue/checking.h"

class ExprInterpreter : public ExprVisitor
{
public:
	lit::LiteralValue* interpret(Expr* expr) {
		return evaluate(expr);
	}

private:
	lit::LiteralValue* visitLiteralExpr(LiteralExpr* expr) override {
		return expr->value;
	}

	lit::LiteralValue* visitGroup(Group* expr) override {
		return evaluate(expr->expression);
	}

	lit::LiteralValue* visitUnary(Unary* expr) override {
		lit::LiteralValue* right = evaluate(expr->expr);

		switch (expr->op.getType()) {
		case MINUS:
			checkLiteralType(right, { lit::LitType::Number });
			return new lit::LiteralValue(-asDbl(right));

		case BANG:
			return new lit::LiteralValue(!isTruthy(right));
		}

		return nullptr;
	}

	lit::LiteralValue* visitBinary(Binary* expr) override {
		lit::LiteralValue* left = evaluate(expr->left);
		lit::LiteralValue* right = evaluate(expr->right);

		switch (expr->op.getType()) {
		case AND:
			return lit::lit(isTruthy((left)) && isTruthy(right));

		case OR:
			return lit::lit(isTruthy(left) || isTruthy(right));

		case GREATER:
			checkLiteralType({ left, right }, { lit::LitType::Number });
			return lit::lit(asDbl(left) > asDbl(right));

		case LESS:
			checkLiteralType({ left, right }, { lit::LitType::Number });
			return lit::lit(asDbl(left) < asDbl(right));

		case GREATER_EQUAL:
			checkLiteralType({ left, right }, { lit::LitType::Number });
			return lit::lit(asDbl(left) >= asDbl(right));

		case LESS_EQUAL:
			checkLiteralType({ left, right }, { lit::LitType::Number });
			return lit::lit(asDbl(left) <= asDbl(right));

		case BANG_EQUAL: return lit::lit(!isEqual(left, right));
		case EQUAL:
			checkLiteralType({ left, right }, { lit::LitType::Number, lit::LitType::Literal, lit::LitType::Bool, 
												lit::LitType::List, lit::LitType::Object });
			*left = *right; // assignment using pointers
			return left;

		case EQUAL_EQUAL: return lit::lit(isEqual(left, right));
		case EQUAL_EQUAL_EQUAL: return lit::lit(isEqual(left, right, true));

		case PLUS:
			if (lit::LiteralValue::typeof(left) == lit::LitType::Literal || lit::LiteralValue::typeof(right) == lit::LitType::Literal)
				return lit::lit(litToStr(left) + litToStr(right));

			else {
				checkLiteralType({ left, right }, { lit::LitType::Number });
				return lit::lit(asDbl(left) + asDbl(right));
			}

		case MINUS:
			checkLiteralType({ left, right }, { lit::LitType::Number });
			return lit::lit(asDbl(left) - asDbl(right));

		case STAR:
			checkLiteralType({ left, right }, { lit::LitType::Number });
			return lit::lit(asDbl(left) * asDbl(right));

		case SLASH:
			checkLiteralType({ left, right }, { lit::LitType::Number });
			return lit::lit(asDbl(left) / asDbl(right));
		}

		return nullptr;
	}


	lit::LiteralValue* evaluate(Expr* expr) {
		return expr->accept(this);
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

	void checkLiteralType(lit::LiteralValue* value, const std::vector<lit::LiteralValue::Type>& expectedTypes) {
		for (const lit::LiteralValue::Type type : expectedTypes)
			if (lit::isTypeof(value, type))
				return;
		
		throw SystemException(ExprInterpreterError, lit::getTypeAsString(expectedTypes) + " expected: " + litToStr(value, true), ExceptionRef(USER_INPUT));
	}

	void checkLiteralType(const std::vector<lit::LiteralValue*>& vals, const std::vector<lit::LiteralValue::Type>& expectedTypes) {
		for (lit::LiteralValue* value : vals)
			checkLiteralType(value, expectedTypes);
	}
};