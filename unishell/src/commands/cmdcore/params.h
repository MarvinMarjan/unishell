#pragma once

#include "../../system/exception/system_exception.h"
#include "../../algorithm/vector/item.h"
#include "../../data/litvalue/litformat.h"

#include "args.h"

class Param;

using ParamVec = std::vector<Param>;

class Param
{
public:
	Param(lit::LiteralValue* defaultValue = nullptr, const std::vector<lit::LitType>& paramTypes = { lit::LitType::Any }) :
		defaultValue(defaultValue), paramTypes(paramTypes)
	{}

	lit::LiteralValue* getDefaultValue() const noexcept {
		return defaultValue;
	}

	std::vector<lit::LitType> getParamTypes() const noexcept {
		return paramTypes;
	}

	StringList getParamTypesAsString() const noexcept {
		StringList types;

		for (const lit::LitType type : getParamTypes())
			types.push_back(lit::getTypeAsString(type));

		return types;
	}

private:
	lit::LiteralValue* defaultValue;
	std::vector<lit::LitType> paramTypes;
};


class ParamList : public ParamVec
{
public:
	size_t getRequiredParams() const {
		size_t count = 0;

		for (const Param& param : (*this))
			if (!param.getDefaultValue())
				count++;

		return count;
	}
	
	Param get(const size_t index) const {
		for (size_t i = 0; i < size(); i++)
			if (i == index)
				return (*this)[index];

		throw SystemException(CommandError, "Invalid param (index): " + index);
	}

	void match(ArgList& args) const {
		const int count = (int)(size() - args.size());
		lit::LiteralValue* defaultVal;

		// comparations with unsigned and signed can have trouble. use "(int)i"
		for (size_t i = 1; (int)i <= count; i++)
			if ((defaultVal = (*this)[args.size() - 1 + i].getDefaultValue()))
				args.push_back(defaultVal);
	}
};

inline bool checkParamType(const lit::LitTypeList& types, const lit::LitType type) {
	if (alg::vector::exists(types, lit::LitType::Any)) return true;
	else if (alg::vector::exists(types, type)) return true;

	return false;
}

inline std::string stringifyParamTypes(const lit::LitTypeList& types, const bool colorize = false) {
	std::string str = "";
	
	for (size_t i = 0; i < types.size(); i++) {
		const std::string stype = lit::getTypeAsString(types[i]);

		str += ((colorize) ? lit::colorizeStrType(stype) : stype)
			+ ((i + 1 >= types.size()) ? "" : " | ");
	}

	return str;
}