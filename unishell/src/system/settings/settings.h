#pragma once

#include "option.h"

struct SettingsException {
	std::string optionName;
};

class Settings
{
public:
	Settings() {}

	// returns the value of an option "name" or throws a
	// exception if couldn't find
	lit::LiteralValue* operator[](const std::string& name) const {
		return getOption(name).value();
	}

	Option& getOption(const std::string& name) const {
		for (Option option : options_)
			if (option.name() == name)
				return option;

		throw SettingsException { .optionName = name };
	}

	std::vector<Option> getAllOptions() const noexcept {
		return options_;
	}

private:
	friend class System;

	void addOption(const Option& option) noexcept {
		options_.push_back(option);
	}

	std::vector<Option> options_;
};