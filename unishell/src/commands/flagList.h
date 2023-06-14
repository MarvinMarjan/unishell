#pragma once

#include "../utilities/stringUtil.h"

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
