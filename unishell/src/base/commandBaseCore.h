#pragma once

#include "../commands/paramList.h"

template <typename T>
class CommandBaseCore
{
public:
	CommandBaseCore(ParamList params, ArgList args) :
		params(params)
	{
		// default value assignment
		params.match(args);
		
		if (args.size() < params.getRequiredParams())
			throw SystemException(CommandError, "Insufficient arguments", ExceptionRef(USER_INPUT));

		// check if the type of argument is acceptable
		for (size_t i = 0; i < params.size(); i++)
			if (!VectorUtil::exists(params[i].getParamTypes(), getValueType(args[i])) && params[i].getParamTypes().size())
				throw SystemException(CommandError, "Type of argument " + tostr(i + 1) + " unacceptable");
		
		this->args = args;
	}

	virtual T exec() = 0;

protected:
	ArgList args;
	ParamList params;
};

class CommandBase : public CommandBaseCore<void> 
{
public:
	CommandBase(const ParamList& params, const ArgList& args) : 
		CommandBaseCore(params, args) {}
};

class RetCommandBase : public CommandBaseCore<LiteralValue*> 
{
public:
	RetCommandBase(const ParamList& params, const ArgList& args) : 
		CommandBaseCore(params, args) {}
};