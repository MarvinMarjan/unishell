#pragma once

#include "../utilities/stringUtil.h"
#include "../parser/expression/type.h"
#include "../parser/instream/token.h"

class Identifier;

typedef std::vector<Identifier> IdentifierList;

class Identifier
{
public:
	Identifier(const std::string& name, LiteralValue* value, bool sysId = false) : 
		name(name), value(value), sysId(sysId)
	{
		updateType();
	}

	inline std::string getName() const noexcept {
		return name;
	}

	inline LiteralValue* getValue() const noexcept {
		return value;
	}

	constexpr inline IdValueType getType() const noexcept {
		return type;
	}

	inline void setValue(LiteralValue* value) noexcept {
		if (sysId) return; // sys identifiers are const
		this->value = value;
		updateType();
 	}

	constexpr inline bool isSysId() const noexcept {
		return sysId;
	}

private:
	inline void updateType() {
		type = (value) ? (IdValueType)value->index() : Null;
	}

	std::string name;
	LiteralValue* value;
	IdValueType type;

	bool sysId;
};
