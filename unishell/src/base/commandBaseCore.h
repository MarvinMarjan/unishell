#pragma once

#include "../commands/paramList.h"
#include "../commands/flagList.h"

#define THROW_COMMAND_ERR(msg) throw SystemException(CommandError, "(" + cmdSymbol + ") " + msg)

struct CommandHelpData;

enum class CmdFunc
{
	Type,
	Literal,
	Number,
	List,
	Object,

	System,
	Filesystem
};

// exec return type
template <typename T>
class CommandBaseCore
{
public:
	CommandBaseCore() {}
	CommandBaseCore(ParamList params, ArgList args, FlagList flags, const std::string cmdSymbol) :
		params(params), flags(flags)
	{
		// default value assignment, if possible
		params.match(args);
		
		// arguments insufficient
		checkArgumentCount(params, args, cmdSymbol);

		// check if the type of argument is acceptable
		checkArgumentsType(params, args, cmdSymbol);
		
		this->args = args;
	}

	virtual T exec() = 0;

	virtual CommandHelpData help() = 0;

protected:
	ArgList args;
	FlagList flags;
	ParamList params;

private:
	inline void checkArgumentsType(const ParamList& params, const ArgList& args, const std::string& cmdSymbol) {
		for (size_t i = 0; i < params.size(); i++)
			if (!checkParamType(params[i].getParamTypes(), getValueType(args[i])) && params[i].getParamTypes().size())
				THROW_COMMAND_ERR("Type of argument " + tostr(i + 1) +
					" unacceptable: " + litToStr(args[i], true) + "\n     Acceptable types: " +
					stringifyParamTypes(params[i].getParamTypes(), true));
	}

	inline void checkArgumentCount(const ParamList& params, const ArgList& args, const std::string& cmdSymbol) {
		if (args.size() < params.getRequiredParams())
			THROW_COMMAND_ERR("(" + cmdSymbol + ") " + "Insufficient arguments");
	}
};

// main command base
class CommandBase : public CommandBaseCore<void> 
{
public:
	CommandBase() : CommandBaseCore() {}
	CommandBase(const ParamList& params, const ArgList& args, const FlagList& flags, const std::string& cmdSymbol) : 
		CommandBaseCore(params, args, flags, cmdSymbol) {}
};

// return command bases
class RetCommandBase : public CommandBaseCore<LiteralValue*> 
{
public:
	RetCommandBase() : CommandBaseCore() {}
	RetCommandBase(const ParamList& params, const ArgList& args, const FlagList& flags, const std::string& cmdSymbol) :
		CommandBaseCore(params, args, flags, cmdSymbol) {}
};