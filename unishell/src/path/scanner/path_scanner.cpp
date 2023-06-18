#include "path_scanner.h"



void PathScanner::scanToken() {
	const char ch = advance();

	switch (ch)
	{
	case '.':
		if (match('.'))
			addToken(PathToken::TwoDots);

		else if (alg::string::isAlphaNumeric(peek()))
			identifier();

		else
			addToken(PathToken::Dot);
		
		break;

	case '\\':
	case '/':
		addToken(PathToken::DirSeparator);
		break;

	default:
		identifier();
		break;
	}
}