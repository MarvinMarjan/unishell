#pragma once

#include "../commands/argList.h"
#include "../system/systemException.h"

class CommandBase
{
public:
	CommandBase(ArgList args, int argSize = 0) : args(args), argSize(argSize) {
		if (args.size() < argSize)
			throw SystemException(CommandError, "Insufficient arguments", ExceptionRef(USER_INPUT));
	}

	virtual void exec() = 0;

	const int argSize;

protected:
	ArgList args;
};