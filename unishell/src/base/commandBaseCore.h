#pragma once

#include "../commands/paramList.h"

template <typename T>
class CommandBaseCore
{
public:
	CommandBaseCore(ParamList params, ArgList args) :
		params(params)
	{
		if (args.size() < params.getRequiredParams()) {
			params.match(args);

			if (args.size() < params.getRequiredParams())
				throw SystemException(CommandError, "Insufficient arguments", ExceptionRef(USER_INPUT));
		}

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