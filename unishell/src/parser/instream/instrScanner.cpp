#include "instrScanner.h"

TokenList InstreamScanner::scanTokens() {
	while (!isAtEnd()) {
		start = current;
		scanToken();
	}

	return tokens;
}



void InstreamScanner::scanToken()
{
	char ch = advance();

	switch (ch)
	{
	case ' ':
	case ';':
	case ',':
	case '\r':
	case '\t':
		break;

	case '+': addToken(PLUS); break;
	case '-': addToken(MINUS); break;
	case '*': addToken(STAR); break;
	case '/': addToken(SLASH); break;

	case '=': addToken((match('=') ? (match('=') ? EQUAL_EQUAL_EQUAL : EQUAL_EQUAL) : EQUAL)); break;

	case '!': addToken((match('=') ? BANG_EQUAL : BANG)); break;
	case '<': addToken((match('=') ? LESS_EQUAL : LESS)); break;
	case '>': addToken((match('=') ? GREATER_EQUAL : GREATER)); break;

	// TODO: make the scanner interpret these as expressions
	case '(': addToken(LPAREN); break;
	case ')': addToken(RPAREN); break;

	case '{': addToken(LBRACE); break;
	case '}': addToken(RBRACE); break;

	case '\"': string(); break;
	case '$': word(IDENTIFIER); break;
	case '#': word(RETCOMMAND); break;
	case '@': word(INRETCOMMAND); break;

	case ':': addToken(COLON); break;

	default:
		if (tokens.empty() && !ignoreCommand) word(COMMAND);

		else if (StringUtil::isDigit(ch)) {
			if (ch == '.' && StringUtil::isDigit(peek()) && peek() != '.') number();
			else if (ch != '.') number();
			else throw SystemException(InstreamScannerError, "Unexpected token", ExceptionRef(src, current - 1));
		}

		else if (!keyword() && !boolean()) word(LITERAL, true);
	}
}