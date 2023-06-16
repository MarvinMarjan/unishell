#include "args.h"


ArgList getArgs(const TokenList& input, const bool encapsulate, const bool firstIsCommand, bool* hasExplicitList) {
	const size_t index = (firstIsCommand) ? 1 : 0;

	if (input.size() <= index)
		return ArgList(); // has no args

	if (encapsulate) {
		size_t i = index;
		for (i; i < input.size(); i++) {}
		return ArgList(TokenList(input.begin() + index, input.begin() + i));
	}

	else if (input[index].getType() == LIST) {
		if (hasExplicitList != nullptr)
			*hasExplicitList = true;

		return ArgList(input[index]);
	}

	return ArgList();
}