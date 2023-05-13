#include "pathHandler.h"

PathHandler::PathHandler(const std::string& path) {
	setPath(path);

	canManip = true;
}

void PathHandler::manip(TokenList instructions) {
	canManip = true;

	for (PathToken token : instructions)
		switch (token.getType())
		{
		case Dot:
			canManip = false;
			break;

		case DirSeparator:
			canManip = true;
			break;

		case TwoDots:
			if (!canManip) break;

			back();
			canManip = false;
			break;

		case Indentifier:
			if (!canManip) break;

			into(token.getLexical());
			canManip = false;
			break;

		case Root:
			if (!canManip) break;

			into(token.getLexical(), true);
			break;
		}
}