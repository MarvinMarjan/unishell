#pragma once

#include "../commands/paramList.h"

#define THROW_COMMAND_ERR(msg) throw SystemException(CommandError, "(" + cmdSymbol + ") " + msg)

// exec return type
template <typename T>
class CommandBaseCore
{
public:
	CommandBaseCore(ParamList params, ArgList args, const std::string cmdSymbol) :
		params(params)
	{
		// default value assignment, if possible
		params.match(args);
		
		// arguments insufficient
		if (args.size() < params.getRequiredParams())
			throw SystemException(CommandError, "(" + cmdSymbol + ") " + "Insufficient arguments");

		// check if the type of argument is acceptable
		for (size_t i = 0; i < params.size(); i++)
			if (!checkParamType(params[i].getParamTypes(), getValueType(args[i])) && params[i].getParamTypes().size())
				THROW_COMMAND_ERR("Type of argument " + tostr(i + 1) + 
					" unacceptable: " + litToStr(args[i], true) + "\n     Acceptable types: " + 
					stringifyParamTypes(params[i].getParamTypes(), true));
		
		this->args = args;
	}

	virtual T exec() = 0;

protected:
	ArgList args;
	ParamList params;
};

// main command base
class CommandBase : public CommandBaseCore<void> 
{
public:
	CommandBase(const ParamList& params, const ArgList& args, const std::string& cmdSymbol) : 
		CommandBaseCore(params, args, cmdSymbol) {}
};

// return command bases
class RetCommandBase : public CommandBaseCore<LiteralValue*> 
{
public:
	RetCommandBase(const ParamList& params, const ArgList& args, const std::string& cmdSymbol) :
		CommandBaseCore(params, args, cmdSymbol) {}
};