#pragma once

#include "../expr.h"
#include "../../utilities/typeUtil.h"

class ExprInterpreter : public ExprVisitor
{
public:
	LiteralValue* interpret(Expr* expr) {
		return evaluate(expr);
	}

private:
	constexpr LiteralValue* visitLiteralExpr(LiteralExpr* expr) override {
		return expr->value;
	}

	constexpr LiteralValue* visitGroup(Group* expr) override {
		return evaluate(expr->expression);
	}

	constexpr LiteralValue* visitUnary(Unary* expr) override {
		LiteralValue* right = evaluate(expr->expr);

		switch (expr->op.getType()) {
		case MINUS:
			checkLiteralType(right, { Number });
			return new LiteralValue(-asDbl(right));

		case BANG:
			return new LiteralValue(!isTruthy(right));
		}

		return nullptr;
	}

	constexpr LiteralValue* visitBinary(Binary* expr) override {
		LiteralValue* left = evaluate(expr->left);
		LiteralValue* right = evaluate(expr->right);

		switch (expr->op.getType()) {
		case AND:
			return lit(isTruthy((left)) && isTruthy(right));

		case OR:
			return lit(isTruthy(left) || isTruthy(right));

		case GREATER:
			checkLiteralType({ left, right }, { Number });
			return lit(asDbl(left) > asDbl(right));

		case LESS:
			checkLiteralType({ left, right }, { Number });
			return lit(asDbl(left) < asDbl(right));

		case GREATER_EQUAL:
			checkLiteralType({ left, right }, { Number });
			return lit(asDbl(left) >= asDbl(right));

		case LESS_EQUAL:
			checkLiteralType({ left, right }, { Number });
			return lit(asDbl(left) <= asDbl(right));

		case BANG_EQUAL: return lit(!isEqual(left, right));
		case EQUAL:
			checkLiteralType({ left, right }, { Number, Literal, Bool, List, Object });
			*left = *right; // assignment using pointers
			return left;

		case EQUAL_EQUAL: return lit(isEqual(left, right));
		case EQUAL_EQUAL_EQUAL: return lit(isEqual(left, right, true));

		case PLUS:
			if (getValueType(left) == Literal || getValueType(right) == Literal)
				return lit(litToStr(left) + litToStr(right));

			else {
				checkLiteralType({ left, right }, { Number });
				return lit(asDbl(left) + asDbl(right));
			}

		case MINUS:
			checkLiteralType({ left, right }, { Number });
			return lit(asDbl(left) - asDbl(right));

		case STAR:
			checkLiteralType({ left, right }, { Number });
			return lit(asDbl(left) * asDbl(right));

		case SLASH:
			checkLiteralType({ left, right }, { Number });
			return lit(asDbl(left) / asDbl(right));
		}

		return nullptr;
	}


	constexpr LiteralValue* evaluate(Expr* expr) {
		return expr->accept(this);
	}
	
	constexpr bool isTruthy(LiteralValue* value) {
		if (!value) return false;
		if (value->type() == Bool) return asBool(value);

		return true;
	}

	constexpr bool isEqual(LiteralValue* a, LiteralValue* b, const bool strict = false) {
		if (!a && !b) return true;
		if (!a) return false;

		if (!strict)
			return (litToStr(a) == litToStr(b));
		
		// strict equality
		if (a->type() != b->type()) return false;
		
		return (litToStr(a) == litToStr(b));
	}

	constexpr void checkLiteralType(LiteralValue* value, const std::vector<LiteralValueType>& expectedTypes) {
		for (const LiteralValueType type : expectedTypes)
			if (TypeUtil::isTypeof(value, type))
				return;
		
		throw SystemException(ExprInterpreterError, TypeUtil::getTypeAsString(expectedTypes) + " expected: " + litToStr(value, true), ExceptionRef(USER_INPUT));
	}

	constexpr void checkLiteralType(const std::vector<LiteralValue*>& vals, const std::vector<LiteralValueType>& expectedTypes) {
		for (LiteralValue* value : vals)
			checkLiteralType(value, expectedTypes);
	}
};