#pragma once

#include "../utilities/stringUtil.h"
#include "../parser/expression/type.h"
#include "../parser/instream/token.h"

class Identifier;

typedef std::vector<Identifier> IdentifierList;

class Identifier
{
public:
	Identifier(const std::string& name, LiteralValue* value) : name(name), value(value) {
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
		this->value = value;
		updateType();
 	}

private:
	inline void updateType() {
		type = (IdValueType)value->index();
	}

	std::string name;
	LiteralValue* value;
	IdValueType type;
};
