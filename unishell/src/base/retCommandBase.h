#pragma once

#include "../parser/expression/type.h"

#include "../commands/argList.h"
#include "../commands/paramList.h"

class RetCommandBase
{
public:
	RetCommandBase(ParamList params, ArgList args) :
		params(params)
	{
		if (args.size() < params.getRequiredParams()) {
			params.match(args);

			if (args.size() < params.getRequiredParams())
				throw SystemException(CommandError, "Insufficient arguments", ExceptionRef(USER_INPUT));
		}

		this->args = args;
	}

	virtual LiteralValue* exec() = 0;

protected:
	ArgList args;
	ParamList params;
};