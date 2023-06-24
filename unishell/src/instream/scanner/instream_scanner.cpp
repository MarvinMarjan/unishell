#include "instream_scanner.h"

TokenList InstreamScanner::scanTokens() {
	while (!isAtEnd()) {
		start = current;
		scanToken();
	}

	return tokens;
}



void InstreamScanner::scanToken()
{
	const char ch = advance();

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

	case '(': addToken(LPAREN); break;
	case ')': addToken(RPAREN); break;

	case '[': addToken(LBRACKET); break;
	case ']': addToken(RBRACKET); break;

	case '{': addToken(LBRACE); break;
	case '}': addToken(RBRACE); break;

	case '\"': string('\"'); break;
	case '\'': string('\''); break;

	case '`': string('`', true); break;
	case '$': word(IDENTIFIER); break;
	case '%': word(FLAG); break;
	case '#': word(RETCOMMAND); break;
	case '@': word(INRETCOMMAND); break;

	case ':': addToken(COLON); break;

	default:
		if (tokens.empty() && !ignoreCommand) word(COMMAND);

		else if (alg::string::isDigit(ch)) {
			if (ch == '.' && alg::string::isDigit(peek()) && peek() != '.') number();
			else if (ch != '.') number();
			else throw SystemException(InstreamScannerError, "Unexpected token", ExceptionRef(src, current - 1));
		}

		else if (!keyword() && !boolean()) word(LITERAL, true);
	}
}


void InstreamScanner::string(const char delimiter, const bool raw)
{
	while (peek() != delimiter) {
		if (isAtEnd())
			throw SystemException(InstreamScannerError, "Unterminated string", ExceptionRef(USER_INPUT, current - 1));

		if (advance() != '\\' || raw) continue;

		// escape character processing
		addEscapeChar();
	}

	addToken(LITERAL, new lit::LiteralValue(src.substr(start + 1, current - 1 - start)));
	advance(); // closing char
}