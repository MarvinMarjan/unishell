#pragma once

#include "expr.h"
#include "../../utilities/typeUtil.h"

class ExprInterpreter : public ExprVisitor
{
public:
	inline LiteralValue* interpret(Expr* expr) {
		return evaluate(expr);
	}

private:
	LiteralValue* visitLiteralExpr(LiteralExpr* expr) override {
		return expr->value;
	}

	LiteralValue* visitGroup(Group* expr) override {
		return evaluate(expr->expression);
	}

	LiteralValue* visitUnary(Unary* expr) override {
		LiteralValue* right = evaluate(expr->expr);

		switch (expr->op.getType()) {
		case MINUS:
			checkLiteralType(right, { Number }, "Number");
			return new LiteralValue(-asDbl(right));

		case BANG:
			return new LiteralValue(!isTruthy(right));
		}

		return nullptr;
	}

	LiteralValue* visitBinary(Binary* expr) override {
		LiteralValue* left = evaluate(expr->left);
		LiteralValue* right = evaluate(expr->right);

		switch (expr->op.getType()) {
		case AND:
			return new LiteralValue(isTruthy((left)) && isTruthy(right));

		case OR:
			return new LiteralValue(isTruthy(left) || isTruthy(right));

		case GREATER:
			checkLiteralType({ left, right }, { Number }, "Number");
			return new LiteralValue(asDbl(left) > asDbl(right));

		case LESS:
			checkLiteralType({ left, right }, { Number }, "Number");
			return new LiteralValue(asDbl(left) < asDbl(right));

		case GREATER_EQUAL:
			checkLiteralType({ left, right }, { Number }, "Number");
			return new LiteralValue(asDbl(left) >= asDbl(right));

		case LESS_EQUAL:
			checkLiteralType({ left, right }, { Number }, "Number");
			return new LiteralValue(asDbl(left) <= asDbl(right));

		case BANG_EQUAL: return new LiteralValue(!isEqual(left, right));
		case EQUAL:
			checkLiteralType({ left, right }, { Number, Literal, Bool }, "Number | Literal | Bool");
			*left = *right; // assignment using pointers
			return left;

		case EQUAL_EQUAL: return new LiteralValue(isEqual(left, right));
		case EQUAL_EQUAL_EQUAL: return new LiteralValue(isEqual(left, right, true));

		case PLUS:
			if (getValueType(left) == Literal || getValueType(right) == Literal)
				return new LiteralValue(litToStr(left) + litToStr(right));

			else {
				checkLiteralType({ left, right }, { Number }, "Number");
				return new LiteralValue(asDbl(left) + asDbl(right));
			}

		case MINUS:
			checkLiteralType({ left, right }, { Number }, "Number");
			return new LiteralValue(asDbl(left) - asDbl(right));

		case STAR:
			checkLiteralType({ left, right }, { Number }, "Number");
			return new LiteralValue(asDbl(left) * asDbl(right));

		case SLASH:
			checkLiteralType({ left, right }, { Number }, "Number");
			return new LiteralValue(asDbl(left) / asDbl(right));
		}

		return nullptr;
	}


	inline LiteralValue* evaluate(Expr* expr) {
		return expr->accept(this);
	}

	inline bool isTruthy(LiteralValue* value) {
		if (!value) return false;
		if (getValueType(value) == Bool) return asBool(value);
		return true;
	}

	inline bool isEqual(LiteralValue* a, LiteralValue* b, bool strict = false) {
		if (!a && !b) return true;
		if (!a) return false;

		if (!strict)
			return (litToStr(a) == litToStr(b));
		
		// strict equality
		if (getValueType(a) != getValueType(b)) return false;
		
		return (litToStr(a) == litToStr(b));
	}

	inline void checkLiteralType(LiteralValue* value, std::vector<IdValueType> expectedTypes, const std::string& typeStr) {
		for (IdValueType type : expectedTypes)
			if (TypeUtil::isTypeof(value, type))
				return;
		
		throw SystemException(ExprInterpreterError, typeStr + " expected: " + litToStr(value, true), ExceptionRef(USER_INPUT));
	}

	inline void checkLiteralType(std::vector<LiteralValue*> vals, std::vector<IdValueType> expectedTypes, const std::string& typeStr) {
		for (LiteralValue* value : vals)
			checkLiteralType(value, expectedTypes, typeStr);
	}
};