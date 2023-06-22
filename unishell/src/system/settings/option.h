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
	friend std::string formatOption(const Option&) noexcept;

	std::string name_;
	lit::LiteralValue* value_;

	bool valueRepresentsColor_;
};