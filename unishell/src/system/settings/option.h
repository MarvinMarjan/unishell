#pragma once

#include "../../data/litvalue/type.h"
#include "../../algorithm/bit/operations.h"


enum OptionFlag
{
	ValueRepresentsColor = 0x01,
};


class Option
{
public:
	Option(const std::string& name, lit::LiteralValue* value, const int flags)
		: name_(name), value_(value)
	{
		valueRepresentsColor_ = alg::bit::hasBits(flags, ValueRepresentsColor);
	}

	constexpr std::string name() const noexcept {
		return name_;
	}

	constexpr lit::LiteralValue* value() const noexcept {
		return value_;
	}

	constexpr void setValue(lit::LiteralValue* value) noexcept {
		value_ = value;
	}


private:
	friend class Settings;
	friend std::string formatOption(const Option&, const int) noexcept;

	std::string name_;
	lit::LiteralValue* value_;

	bool valueRepresentsColor_;
};



class Section
{
public:
	explicit Section(std::vector<Option> options)
		: options_(options)
	{}

	Option* getOption(const std::string& name) noexcept {
		for (size_t i = 0; i < options_.size(); i++)
			if (options_[i].name() == name)
				return &options_[i];

		return nullptr;
	}

	std::vector<Option> getAllOptions() const noexcept {
		return options_;
	}

private:
	friend class Settings;

	std::vector<Option>& getAllOptionsRef() noexcept {
		return options_;
	}


	std::vector<Option> options_;
};
