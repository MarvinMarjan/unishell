#pragma once

#include "option.h"


class Settings
{
public:
	Settings() {}

	// returns the value of an option "name" or throws a
	// exception if couldn't find
	lit::LiteralValue* operator[](const std::string& name) {
		return getOption(name)->value();
	}

	Option* getOption(const std::string& name) {
		for (size_t i = 0; i < options_.size(); i++)
			if (options_[i].getOption(name))
				return options_[i].getOption(name);

		return nullptr;
	}

	Option* getOption(const size_t index) {
		int total = 0;

		for (size_t i = 0; i < options_.size(); i++)
			for (size_t o = 0; o < options_[i].getAllOptions().size(); o++, total++)
				if (total == index)
					return &options_[i].getAllOptionsRef()[o];

		return nullptr;
	}

	std::vector<Section> getAllSections() const noexcept {
		return options_;
	}

private:
	friend class System;

	void addSection(const Section& option) noexcept {
		options_.push_back(option);
	}

	std::vector<Section> options_;
};