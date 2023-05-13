#include "scanner.h"

InputScanner::InputScanner(const std::string& src) {
	start = 0;
	current = 0;

	this->src = src;
}

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