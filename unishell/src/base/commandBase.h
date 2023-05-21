#pragma once

#include "../commands/argList.h"
#include "../commands/paramList.h"

#include "../system/systemException.h"

class CommandBase
{
public:
	CommandBase(ParamList params, ArgList args) : 
		params(params) 
	{
		if (args.size() < params.getRequiredParams()) {
			params.match(args);

			if (args.size() < params.getRequiredParams())
				throw SystemException(CommandError, "Insufficient arguments", ExceptionRef(USER_INPUT));
		}

		this->args = args;
	}

	virtual void exec() = 0;

protected:
	ArgList args;
	ParamList params;
};