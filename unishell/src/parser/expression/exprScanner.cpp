#include "exprScanner.h"

ExprTokenList ExprScanner::scanTokens() {
	while (!isAtEnd()) {
		start = current;
		scanToken();
	}

	return tokens;
}

void ExprScanner::scanToken() {
	char ch = advance();

	switch (ch)
	{
	case ' ':
	case '\t':
		break;

	case '+': addToken(PLUS); break;
	case '-': addToken(MINUS); break;

	case '*': addToken(STAR); break;
	case '/': addToken(SLASH); break;

	case '=': 
		if (match('='))	addToken(EQUAL_EQUAL);
		else throw SystemException(ExprScannerError, UNEXPECTED_TOKEN_MSG, ExceptionRef(src, current - 1)); // single '=' not allowed
		break;

	case '!': addToken((match('=') ? BANG_EQUAL : BANG)); break;
	case '<': addToken((match('=') ? LESS_EQUAL : LESS)); break;
	case '>': addToken((match('=') ? GREATER_EQUAL : GREATER)); break;

	case '(': addToken(LPAREN); break;
	case ')': addToken(RPAREN); break;

	default:
		if (StringUtil::isDigit(ch)) number();

		else if (!keyword())
			throw SystemException(ExprScannerError, UNEXPECTED_TOKEN_MSG, ExceptionRef(src, current - 1));
	}
}