#pragma once

#include "../data/type.h"

class Identifier;

typedef std::vector<Identifier> IdentifierList;

class Identifier
{
public:
	Identifier(const std::string& name, LiteralValue* value, const bool sysId = false) : 
		name(name), value(value), sysId(sysId)
	{
		updateType();
	}

	std::string getName() const noexcept {
		return name;
	}

	LiteralValue* getValue() const noexcept {
		return value;
	}

	LiteralValueType getType() const noexcept {
		return type;
	}

	void setValue(LiteralValue* value) noexcept {
		if (sysId) return; // sys identifiers are const
		this->value = value;
		updateType();
 	}

	constexpr bool isSysId() const noexcept {
		return sysId;
	}

private:
	void updateType() noexcept {
		type = (value) ? (LiteralValueType)value->index() : Null;
	}

	std::string name;
	LiteralValue* value;
	LiteralValueType type;

	bool sysId;
};
