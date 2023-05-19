#pragma once

#include "identifier.h"

class Environment
{
public:
	Environment() {}
	
	inline Identifier* getId(const std::string& name) noexcept {
		for (size_t i = 0; i < idList.size(); i++)
			if (idList[i].getName() == name)
				return &idList[i];

		return nullptr;
	}

	inline void addId(const Identifier& id) {
		idList.push_back(id);
	}

private:
	IdentifierList idList;
};