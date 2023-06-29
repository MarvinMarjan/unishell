#pragma once

#include "identifier/identifier.h"
#include "../system/settings/json_fstream_handle.h"


#define UNISHLL_ENVIRONMENT_DEFAULT_JSON_FILE_PATH "data/env.json"


class Environment
{
public:
	Environment() {
		try {
			data_ = JSONFstreamHandle(UNISHLL_ENVIRONMENT_DEFAULT_JSON_FILE_PATH);
		}
		catch (JSONFstreamHandle::JSONFileNotFound) {
			return;
		}

		loadFromData();
	}

	Identifier* operator[](const std::string& name) {
		return getId(name);
	}

	IdentifierList getIdList() const noexcept {
		return idList;
	}

	StringList getIdNameList() const noexcept {
		StringList nameList;

		for (const Identifier& id : idList)
			nameList.push_back(id.getName());

		return nameList;
	}
	
	Identifier* getId(std::string idName) noexcept {
		checkIdName(idName);
		for (size_t i = 0; i < idList.size(); i++)
			if (idList[i].getName() == idName)
				return &idList[i];

		return nullptr;
	}

	void addId(const Identifier& id, const bool addToData = true) {
		if (exists(id.getName())) {
			if (getId(id.getName())->isSysId())
				return;

			getId(id.getName())->setValue(id.getValue()); // modify value if already exists
		}

		else
			idList.push_back(id);

		if (addToData && !id.isSysId())
			data_["id"][id.getName()] = data_.LiteralValueToJSONValue(id.getValue());
	}

	void delId(std::string idName) {
		checkIdName(idName);
		for (size_t i = 0; i < idList.size(); i++)
			if (idList[i].getName() == idName) {
				idList.erase(idList.begin() + i);
				data_["id"].erase(idName);
			}
	}

	bool exists(std::string idName) const {
		checkIdName(idName);
		for (const Identifier& id : idList)
			if (id.getName() == idName)
				return true;

		return false;
	}

	bool isSysId(std::string idName) {
		checkIdName(idName);
		for (const Identifier& id : idList)
			if (id.getName() == idName && id.isSysId())
				return true;

		return false;
	}


	JSONFstreamHandle& data() noexcept {
		return data_;
	}


private:
	void loadFromData() {
		for (const auto& [key, value] : data_["id"].items())
			addId(Identifier(key, data_.JSONValueToLiteralValue(value)), false);
	}

	static void checkIdName(std::string& name) {
		while (name[0] == '$') name = name.substr(1);
	}

	IdentifierList idList;

	JSONFstreamHandle data_;
};