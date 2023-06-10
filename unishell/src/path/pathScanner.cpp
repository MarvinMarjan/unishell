#include "pathScanner.h"

void PathScanner::scanToken() {
	const char ch = advance();

	switch (ch)
	{
	case '.':
		if (match('.')) addToken(PathToken::TwoDots);
		else addToken(PathToken::Dot);
		break;

	case '\\':
	case '/':
		addToken(PathToken::DirSeparator);
		break;

	default:
		indentifier();
		break;
	}
}