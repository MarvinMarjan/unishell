#pragma once

#include "identifier.h"

class Environment
{
public:
	Environment() {}
	
	inline Identifier* getId(std::string idName) noexcept {
		checkIdName(idName);
		for (size_t i = 0; i < idList.size(); i++)
			if (idList[i].getName() == idName)
				return &idList[i];

		return nullptr;
	}

	inline void addId(const Identifier& id) {
		if (exists(id.getName()))
			getId(id.getName())->setValue(id.getValue()); // modify value if already exists

		else
			idList.push_back(id);
	}

	inline void delId(std::string idName) {
		checkIdName(idName);
		for (size_t i = 0; i < idList.size(); i++)
			if (idList[i].getName() == idName)
				idList.erase(idList.begin() + i);
	}

	inline bool exists(std::string idName) const {
		checkIdName(idName);
		for (const Identifier& id : idList)
			if (id.getName() == idName)
				return true;

		return false;
	}

	inline bool isSysId(std::string idName) {
		checkIdName(idName);
		for (const Identifier& id : idList)
			if (id.getName() == idName && id.isSysId())
				return true;

		return false;
	}

private:
	static inline void checkIdName(std::string& name) {
		while (name[0] == '$') name = name.substr(1);
	}

	IdentifierList idList;
};