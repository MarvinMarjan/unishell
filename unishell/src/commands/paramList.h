#pragma once

#include "../parser/expression/type.h"
#include "../utilities/stringUtil.h"
#include "../utilities/typeUtil.h"
#include "../system/system.h"

#include "argList.h"

class Param;

typedef std::vector<Param> ParamVec;

class Param
{
public:
	Param(LiteralValue* defaultValue = nullptr, const std::vector<LiteralValueType>& paramTypes = {Any}) :
		defaultValue(defaultValue), paramTypes(paramTypes)
	{}

	inline LiteralValue* getDefaultValue() const noexcept {
		return defaultValue;
	}

	inline std::vector<LiteralValueType> getParamTypes() const noexcept {
		return paramTypes;
	}

	inline StringList getParamTypesAsString() const noexcept {
		StringList types;

		for (LiteralValueType type : getParamTypes())
			types.push_back(TypeUtil::getTypeAsString(type));

		return types;
	}

private:
	LiteralValue* defaultValue;
	std::vector<LiteralValueType> paramTypes;
};


class ParamList : public ParamVec
{
public:
	inline size_t getRequiredParams() const {
		size_t count = 0;

		for (const Param& param : (*this))
			if (!param.getDefaultValue())
				count++;

		return count;
	}
	
	inline Param get(const size_t index) const {
		for (size_t i = 0; i < size(); i++)
			if (i == index)
				return (*this)[index];

		throw SystemException(CommandError, "Invalid param (index): " + index);
	}

	inline void match(ArgList& args) const {
		const int count = (int)(size() - args.size());
		LiteralValue* defaultVal;

		// comparations with unsigned and signed can have trouble. use "(int)i"
		for (size_t i = 1; (int)i <= count; i++)
			if ((defaultVal = (*this)[args.size() - 1 + i].getDefaultValue()))
				args.push_back(defaultVal);
	}
};

inline bool checkParamType(const LiteralValueTypeList& types, const LiteralValueType type) {
	if (VectorUtil::exists(types, Any)) return true;
	else if (VectorUtil::exists(types, type)) return true;

	return false;
}

inline std::string stringifyParamTypes(const LiteralValueTypeList& types, bool colorize = false) {
	std::string str = "";
	
	for (size_t i = 0; i < types.size(); i++) {
		const std::string stype = TypeUtil::getTypeAsString(types[i]);

		str += ((colorize) ? TypeUtil::colorizeStrType(stype) : stype)
			+ ((i + 1 >= types.size()) ? "" : " | ");
	}

	return str;
}