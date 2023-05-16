#include "pathHandler.h"

PathHandler::PathHandler(const std::string& path) {
	setPath(path);

	canManip = true;
}

void PathHandler::manip(PathTokenList instructions) {
	canManip = true;

	for (PathToken token : instructions)
		switch (token.getType())
		{
		case PathToken::Dot:
			canManip = false;
			break;

		case PathToken::DirSeparator:
			canManip = true;
			break;

		case PathToken::TwoDots:
			if (!canManip) break;

			back();
			canManip = false;
			break;

		case PathToken::INDENTIFIER:
			if (!canManip) break;

			into(token.getLexical());
			canManip = false;
			break;

		case PathToken::Root:
			if (!canManip) break;

			into(token.getLexical(), true);
			break;
		}
}