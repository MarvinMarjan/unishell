#pragma once

#include "option.h"

#include "../../data/litvalue/litformat.h"
#include "../../filesystem/handle/file.h"
#include "../../algorithm/string/manip.h"
#include "json_fstream_handle.h"


#include <nlohmann/json.hpp>


#define UNISHLL_SETTINGS_DEFAULT_JSON_FILE_PATH "data/setting.json"


using json = nlohmann::json;


class Settings
{
public:
	Settings();

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


	void updateDataFromOptions() {
		for (const Section& section : getAllSections())
			for (const Option& option : section.getAllOptions())
				data_[alg::string::toSnakeCase(option.name())] = JSONFstreamHandle::LiteralValueToJSONValue(option.value());
	}


	JSONFstreamHandle& data() noexcept {
		return data_;
	}

private:
	friend class System;


	void addSection(const Section& section) noexcept {
		sections_.push_back(section);

		for (const Option& option : section.getAllOptions())
			if (!data_.contains(alg::string::toSnakeCase(option.name())))
				data_[alg::string::toSnakeCase(option.name())] = JSONFstreamHandle::LiteralValueToJSONValue(option.value_);
	}



	void updateOptionsFromData() {
		for (const auto& [key, value] : data_.items()) {
			Option* option = getOption(alg::string::snakeCaseToPascal(key));

			if (option)
				option->setValue(JSONFstreamHandle::JSONValueToLiteralValue(value));
		}
	}


	std::vector<Section> sections_;

	JSONFstreamHandle data_;
};