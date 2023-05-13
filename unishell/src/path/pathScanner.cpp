#include "pathScanner.h"

PathScanner::PathScanner(const std::string& src) : src(src) {
	current = 0;
	start = 0;
}

void PathScanner::scanToken() {
	char ch = advance();

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