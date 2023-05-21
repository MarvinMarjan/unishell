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
		if (exists(id.getName()))
			getId(id.getName())->setValue(id.getValue());
		else
			idList.push_back(id);
	}

	inline bool exists(const std::string& name) const {
		for (const Identifier& id : idList)
			if (id.getName() == name)
				return true;

		return false;
	}

private:
	IdentifierList idList;
};