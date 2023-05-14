#include "scanner.h"

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
	case '$': characters(InputToken::Indentifier); break;

	default:
		if (tokens.empty()) characters(InputToken::Command);
		else characters(InputToken::Literal);
	}
}