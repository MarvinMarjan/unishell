#pragma once

#include "../../data/litvalue/type.h"

class Identifier;


using IdentifierList = std::vector<Identifier>;


class Identifier
{
public:
	Identifier(const std::string& name, lit::LiteralValue* value, const bool local = false, const bool sysId = false) : 
		name(name), value(value), local(local), sysId(sysId)
	{
		updateType();
	}

	std::string getName() const noexcept {
		return name;
	}

	lit::LiteralValue* getValue() const noexcept {
		return value;
	}

	lit::LitType getType() const noexcept {
		return type;
	}

	void setValue(lit::LiteralValue* value) noexcept {
		if (sysId) return; // sys identifiers are const
		this->value = value;
		updateType();
 	}

	constexpr bool isSysId() const noexcept {
		return sysId;
	}

	constexpr bool isLocal() const noexcept {
		return local;
	}

private:
	void updateType() noexcept {
		type = (value) ? (lit::LitType)value->index() : lit::LitType::Null;
	}

	std::string name;
	lit::LiteralValue* value;
	lit::LitType type;

	bool sysId;
	bool local;
};
