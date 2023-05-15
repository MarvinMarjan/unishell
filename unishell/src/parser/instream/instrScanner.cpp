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

	case '\"': string(); break;
	case '(': expression(); break;
	case '$': characters(Indentifier); break;

	default:
		if (tokens.empty()) characters(Command);
		else characters(Literal);
	}
}

void InputScanner::expression() {
	unsigned short aux = 0;
	bool isEnclosing = false;

	while (!isAtEnd()) {
		if (peek() == '(') aux++;
		if (peek() == ')' && !aux) {
			isEnclosing = true;
			break;
		}
		else if (peek() == ')' && aux && current + 1 < src.size()) aux--;

		advance();
	}

	// ')' missing in expression
	if (!isEnclosing) 
		throw SystemException(InstreamScannerError, "Unterminated expression", ExceptionRef(src, current - 1));

	addToken(Expression, src.substr(start + 1, current - 1 - start));

	// closing char
	advance(); 
}