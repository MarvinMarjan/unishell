#pragma once

#include "option.h"

#include "../../data/litvalue/litformat.h"
#include "../../filesystem/handle/file.h"

#include <nlohmann/json.hpp>


#define UNISHLL_SETTINGS_DEFAULT_JSON_FILE_PATH "data/data.json"


using json = nlohmann::json;


class Settings
{
public:
	struct JSONFileNotFound {
		std::string path;
	};

	Settings() {
		loadDataFromJSONFile(UNISHLL_SETTINGS_DEFAULT_JSON_FILE_PATH);
	}

	~Settings() = default;


	// returns the value of an option "name" or nullptr
	// if couldn't find
	lit::LiteralValue* operator[](const std::string& name) {
		return getOption(name)->value();
	}

	Option* getOption(const std::string& name) {
		for (size_t i = 0; i < sections_.size(); i++)
			if (sections_[i].getOption(name))
				return sections_[i].getOption(name);

		return nullptr;
	}

	Option* getOption(const size_t index) {
		int total = 0;

		for (size_t i = 0; i < sections_.size(); i++)
			for (size_t o = 0; o < sections_[i].getAllOptions().size(); o++, total++)
				if (total == index)
					return &sections_[i].getAllOptionsRef()[o];

		return nullptr;
	}

	std::vector<Section> getAllSections() const noexcept {
		return sections_;
	}


	void saveDataToJSONFile(const std::string& path) const {
		if (!fsys::File::exists(path))
			throw JSONFileNotFound {.path = path};

		fsys::File::write(path, data_.dump(2));
	}

	void loadDataFromJSONFile(const std::string& path) {
		if (!fsys::File::exists(path))
			throw JSONFileNotFound {.path = path};

		data_ = json::parse(fsys::File::readAsString(path));
	}

	void updateDataFromOptions() {
		for (const Section& section : getAllSections())
			for (const Option& option : section.getAllOptions())
				data_[alg::string::toSnakeCase(option.name())] = LiteralValueToJSONValue(option.value());
	}

private:
	friend class System;


	void addSection(const Section& section) noexcept {
		sections_.push_back(section);

		for (const Option& option : section.getAllOptions())
			if (!data_.contains(alg::string::toSnakeCase(option.name())))
				data_[alg::string::toSnakeCase(option.name())] = LiteralValueToJSONValue(option.value_);
	}



	void updateOptionsFromData() {
		for (const auto& [key, value] : data_.items()) {
			Option* option = getOption(alg::string::snakeCaseToPascal(key));

			if (option)
				option->setValue(JSONValueToLiteralValue(value));
		}
	}



	static lit::LiteralValue* JSONValueToLiteralValue(json data) {
		if (data.is_string()) return new lit::LiteralValue(data.get<std::string>());
		if (data.is_number()) return new lit::LiteralValue(data.get<double>());
		if (data.is_boolean()) return new lit::LiteralValue(data.get<bool>());

		return nullptr;
	}

	static json LiteralValueToJSONValue(lit::LiteralValue* value) {
		if (value->index() == 0) return asStr(value);
		if (value->index() == 1) return asDbl(value);
		if (value->index() == 2) return asBool(value);

		return nullptr;
	}


	std::vector<Section> sections_;

	json data_;
};