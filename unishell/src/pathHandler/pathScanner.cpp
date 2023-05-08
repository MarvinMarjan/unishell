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
		if (match('.')) addToken(TwoDots);
		else addToken(Dot);
		break;

	case '\\':
	case '/':
		addToken(DirSeparator);
		break;

	default:
		indentifier();
		break;
	}
}