#pragma once

#include "../../algorithm/vector/item.h"

#include <string>

struct Flag
{
	std::string name;
};

class FlagList : public std::vector<Flag>
{
public:
	bool hasFlag(const std::string& flagName) const noexcept {
		for (const Flag& flag : (*this))
			if (flag.name == flagName)
				return true;
		
		return false;
	}
};



inline FlagList getFlags(const TokenList& input) noexcept {
	FlagList flags;

	for (const Token& token : input)
		if (token.getType() == FLAG)
			flags.push_back(Flag { .name = token.getLexical().substr(1)});

	return flags;
}

inline void removeFlags(TokenList& input) noexcept {
	std::erase_if(input, [](Token token) {
		return (token.getType() == FLAG);
	});
}