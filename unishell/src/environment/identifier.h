#pragma once

#include "../utilities/stringUtil.h"
#include "../parser/expression/type.h"
#include "../parser/instream/token.h"

class Identifier;

typedef std::vector<Identifier> IdentifierList;

class Identifier
{
public:
	constexpr inline Identifier(const std::string& name, LiteralValue* value, const bool sysId = false) : 
		name(name), value(value), sysId(sysId)
	{
		updateType();
	}

	constexpr std::string getName() const noexcept {
		return name;
	}

	constexpr LiteralValue* getValue() const noexcept {
		return value;
	}

	constexpr LiteralValueType getType() const noexcept {
		return type;
	}

	constexpr void setValue(LiteralValue* value) noexcept {
		if (sysId) return; // sys identifiers are const
		this->value = value;
		updateType();
 	}

	constexpr inline bool isSysId() const noexcept {
		return sysId;
	}

private:
	constexpr void updateType() noexcept {
		type = (value) ? (LiteralValueType)value->index() : Null;
	}

	std::string name;
	LiteralValue* value;
	LiteralValueType type;

	bool sysId;
};
