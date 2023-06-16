#include "exprInterpreter.h"

lit::LiteralValue* ExprInterpreter::visitLiteralExpr(LiteralExpr* expr) {
	return expr->value;
}


lit::LiteralValue* ExprInterpreter::visitGroup(Group* expr) {
	return evaluate(expr->expression);
}


lit::LiteralValue* ExprInterpreter::visitUnary(Unary* expr) {
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


lit::LiteralValue* ExprInterpreter::visitBinary(Binary* expr)
{
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