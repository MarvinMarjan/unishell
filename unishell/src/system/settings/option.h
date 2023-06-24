#pragma once

#include "../../data/litvalue/type.h"
#include "../../algorithm/bit/operations.h"
#include "../../algorithm/vector/item.h"


enum OptionFlag
{
	ValueRepresentsColor = 0x01,
};


class Option
{
public:
	struct InvalidValueTypeErr {
		lit::LiteralValue* value;
		bool expectedColorString;
	};

	
	Option(const std::string& name, lit::LiteralValue* value, void (*onValueChange)(lit::LiteralValue*), 
		const lit::LitTypeList validTypes = { lit::LitType::Any }, const int flags = 0)
		
		: name_(name), value_(value), types_(validTypes), onValueChange_(onValueChange)
	{
		valueRepresentsColor_ = alg::bit::hasBits(flags, ValueRepresentsColor);
	}

	constexpr std::string name() const noexcept {
		return name_;
	}

	constexpr lit::LiteralValue* value() const noexcept {
		return value_;
	}

	constexpr lit::LitTypeList types() const noexcept {
		return types_;
	}


	void setValue(lit::LiteralValue* value) {
		if (!valueIsValid(value))
			throw InvalidValueTypeErr {value, valueRepresentsColor_};

		value_ = value;

		onValueChange_(value_);
	}


private:
	bool valueIsValid(lit::LiteralValue* value);

	friend class Settings;
	friend std::string formatOption(const Option&, const int) noexcept;

	std::string name_;

	lit::LiteralValue* value_;

	lit::LitTypeList types_;

	bool valueRepresentsColor_;

	
	// callback function
	void (*onValueChange_)(lit::LiteralValue*);
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
