#include "pathHandler.h"

PathHandler::PathHandler(const std::string& path) {
	setPath(path);

	canManip = true;
}

bool PathHandler::manip(PathTokenList instructions, bool ignoreExcp) {
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

		case PathToken::IDENTIFIER:
			if (!canManip) break;

			if (!into(token.getLexical(), false, ignoreExcp)) return false;
			canManip = false;
			break;

		case PathToken::Root:
			if (!canManip) break;

			if (!into(token.getLexical(), true, ignoreExcp)) return false;
			break;
		}

	return true;
}