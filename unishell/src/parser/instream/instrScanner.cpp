#include "instrScanner.h"

void InputScanner::scanToken()
{
	char ch = advance();

	switch (ch)
	{
	case ' ':
	case '\r':
	case '\t':
		break;

	case '+': addToken(PLUS); break;
	case '-': addToken(MINUS); break;
	case '*': addToken(STAR); break;
	case '/': addToken(SLASH); break;

	case '=': addToken((match('=') ? EQUAL_EQUAL : EQUAL)); break;

	case '!': addToken((match('=') ? BANG_EQUAL : BANG)); break;
	case '<': addToken((match('=') ? LESS_EQUAL : LESS)); break;
	case '>': addToken((match('=') ? GREATER_EQUAL : GREATER)); break;

	// TODO: make the scanner interpret these as expressions
	case '(': addToken(LPAREN); break;
	case ')': addToken(RPAREN); break;

	case '\"': string(); break;
	case '$': word(INDENTIFIER); break;

	default:
		if (tokens.empty() && !ignoreCommand) word(COMMAND);
		else if (StringUtil::isDigit(ch)) number();
		else if (!keyword()) word(LITERAL);
	}
}

void InputScanner::expression() {
//	unsigned short aux = 0;
//  bool isEnclosing = false;
//
//	while (!isAtEnd()) {
//		if (peek() == '(') aux++;
//		if (peek() == ')' && !aux) {
//			isEnclosing = true;
//			break;
//		}
//		else if (peek() == ')' && aux && current + 1 < src.size()) aux--;
//
//		advance();
//	}
//
//	// ')' missing in expression
//	if (!isEnclosing) 
//		throw SystemException(InstreamScannerError, "Unterminated expression", ExceptionRef(src, current - 1));
//
//	addToken(Expression, src.substr(start + 1, current - 1 - start));
//
//	// closing char
//	advance(); 
}