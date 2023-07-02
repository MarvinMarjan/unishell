#include "instream_scanner.h"

TokenList InstreamScanner::scanTokens()
{
	while (!isAtEnd()) {
		start = current;
		scanToken();
	}

	return tokens;
}


std::vector<TokenList> InstreamScanner::separateLinesFromTokens(TokenList tokens)
{
	std::vector<TokenList> lines;
	TokenList aux;

	for (Token& token : tokens) {
		if (token.getType() == ENDLINE) {
			if (!token.getNestLevel()) {
				lines.push_back(aux);
				aux.clear();
			}
			else {
				token.nestLevel--;
				aux.push_back(token);
			}

			continue;
		}

		aux.push_back(token);
	}

	if (!aux.empty())
		lines.push_back(aux);

	return lines;
}



void InstreamScanner::scanToken()
{
	const char ch = advance();

	switch (ch)
	{
	case ' ':
	case ',':
	case '\r':
	case '\t':
		break;

	case '\n':
		currentLine++;
		break;

	case ';':
		if (addEndlTokens)
			addToken(ENDLINE, nestLevel);
		
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
		if (alg::string::isDigit(ch))
		{
			if (ch == '.' && alg::string::isDigit(peek()) && peek() != '.') number();
			else if (ch != '.') number();
			else throw new InstreamScannerErr("Unexpected token", ExceptionRef(src, current - 1));
		}

		else if (!block() && !keyword() && !boolean())
			word(LITERAL, true);
	}
}


void InstreamScanner::string(const char delimiter, const bool raw)
{
	while (peek() != delimiter) {
		if (isAtEnd())
			throw new InstreamScannerErr("Unterminated string", ExceptionRef(UNISHLL_USER_INPUT, current - 1));

		if (advance() != '\\' || raw) continue;

		// escape character processing
		addEscapeChar();
	}

	addToken(LITERAL, new lit::LiteralValue(src.substr(start + 1, current - 1 - start)));
	advance(); // closing char
}

bool InstreamScanner::block()
{
	const std::string word = advanceWord();

	if (word == "begin") {
		addToken(BEGIN);
		addEndlTokens = true;
		nestLevel++;
	}

	else if (word == "end") {
		addToken(END);

		if (!alg::bit::hasBits(hints, AddEndlTokens))
			addEndlTokens = false;

		nestLevel--;
	}


	return (word == "begin" || word == "end");
}
