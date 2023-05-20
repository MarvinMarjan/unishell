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
			checkLiteralType(right, Number, "Number");
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
			checkLiteralType({ left, right }, Number, "Number");
			return new LiteralValue(asDbl(left) > asDbl(right));

		case LESS:
			checkLiteralType({ left, right }, Number, "Number");
			return new LiteralValue(asDbl(left) < asDbl(right));

		case GREATER_EQUAL:
			checkLiteralType({ left, right }, Number, "Number");
			return new LiteralValue(asDbl(left) >= asDbl(right));

		case LESS_EQUAL:
			checkLiteralType({ left, right }, Number, "Number");
			return new LiteralValue(asDbl(left) <= asDbl(right));

		case BANG_EQUAL: return new LiteralValue(!isEqual(left, right));
		case EQUAL_EQUAL: return new LiteralValue(isEqual(left, right));

		case PLUS:
			if (getValueActiveType(left) == Literal || getValueActiveType(right) == Literal)
				return new LiteralValue(TypeUtil::literalValueToString(left) + TypeUtil::literalValueToString(right));

			else {
				checkLiteralType({ left, right }, Number, "Number");
				return new LiteralValue(asDbl(left) + asDbl(right));
			}

		case MINUS:
			checkLiteralType({ left, right }, Number, "Number");
			return new LiteralValue(asDbl(left) - asDbl(right));

		case STAR:
			checkLiteralType({ left, right }, Number, "Number");
			return new LiteralValue(asDbl(left) * asDbl(right));

		case SLASH:
			checkLiteralType({ left, right }, Number, "Number");
			return new LiteralValue(asDbl(left) / asDbl(right));
		}

		return nullptr;
	}


	inline LiteralValue* evaluate(Expr* expr) {
		return expr->accept(this);
	}

	inline bool isTruthy(LiteralValue* value) {
		if (!value) return false;
		if (getValueActiveType(value) == Bool) return asBool(value);
		return true;
	}

	inline bool isEqual(LiteralValue* a, LiteralValue* b) {
		if (!a && !b) return true;
		if (!a) return false;

		return (TypeUtil::literalValueToString(a) == TypeUtil::literalValueToString(b));
	}

	inline void checkLiteralType(LiteralValue* value, IdValueType expectedType, const std::string& typeStr) {
		if (!TypeUtil::isTypeof(value, expectedType))
			throw SystemException(ExprInterpreterError, typeStr + " expected: " + qtd(TypeUtil::literalValueToString(value)), ExceptionRef(*System::input()));
	}

	inline void checkLiteralType(std::vector<LiteralValue*> vals, IdValueType type, const std::string& typeStr) {
		for (LiteralValue* value : vals)
			checkLiteralType(value, type, typeStr);
	}
};