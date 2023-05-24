#pragma once

#include "../parser/expression/type.h"
#include "../utilities/stringUtil.h"
#include "../system/system.h"

#include "argList.h"

class Param;

typedef std::vector<Param> ParamVec;

class Param
{
public:
	Param(LiteralValue* defaultValue = nullptr, std::vector<IdValueType> paramTypes = {}) :
		defaultValue(defaultValue), paramTypes(paramTypes)
	{}

	inline LiteralValue* getDefaultValue() const noexcept {
		return defaultValue;
	}

	inline std::vector<IdValueType> getParamTypes() const noexcept {
		return paramTypes;
	}

private:
	LiteralValue* defaultValue;
	std::vector<IdValueType> paramTypes;
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

	inline Param get(size_t index) const {
		for (size_t i = 0; i < size(); i++)
			if (i == index)
				return (*this)[index];

		throw SystemException(CommandError, "Invalid param (index): " + index);
	}

	inline void match(ArgList& args) {
		int count = (int)(size() - args.size());
		LiteralValue* defaultVal;

		for (size_t i = 1; i <= count; i++)
			if ((defaultVal = (*this)[args.size() - 1 + i].getDefaultValue()))
				args.push_back(defaultVal);
	}
};

