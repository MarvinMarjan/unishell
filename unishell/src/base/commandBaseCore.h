#pragma once

#include "../commands/paramList.h"
#include "../commands/flagList.h"

#define THROW_COMMAND_ERR(msg) \
	throw SystemException(CommandError, "(" + cmdSymbol + ") " + msg) \

struct CommandHelpData;

enum class CmdFunc
{
	Type,
	Literal,
	Number,
	List,
	Object,

	System,
	Filesystem,
	Regex
};

// exec return type
template <typename T>
class CommandBaseCore
{
public:
	CommandBaseCore() : function(CmdFunc::System) {}
	CommandBaseCore(const std::string& cmdSymbol, const CmdFunc func) : symbol(cmdSymbol), function(func) {}
	CommandBaseCore(const ParamList& params, ArgList args, const FlagList& flags, const std::string& cmdSymbol, const CmdFunc func) :
		params(params), flags(flags), symbol(cmdSymbol), function(func)
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

	const std::string symbol;
	const CmdFunc function;

protected:
	ArgList args;
	FlagList flags;
	ParamList params;

private:
	void checkArgumentsType(const ParamList& params, const ArgList& args, const std::string& cmdSymbol) {
		for (size_t i = 0; i < params.size(); i++)
			if (!checkParamType(params[i].getParamTypes(), lit::LiteralValue::typeof(args[i])) && params[i].getParamTypes().size())
				THROW_COMMAND_ERR("Type of argument " + tostr(i + 1) +
					" unacceptable: " + litToStr(args[i], true) + "\n     Acceptable types: " +
					stringifyParamTypes(params[i].getParamTypes(), true));
	}

	void checkArgumentCount(const ParamList& params, const ArgList& args, const std::string& cmdSymbol) {
		if (args.size() < params.getRequiredParams())
			THROW_COMMAND_ERR("(" + cmdSymbol + ") " + "Insufficient arguments");
	}
};

// main command base
class CommandBase : public CommandBaseCore<void> 
{
public:
	CommandBase() : CommandBaseCore() {}
	CommandBase(const std::string& cmdSymbol, const CmdFunc func) : CommandBaseCore(cmdSymbol, func) {}
	CommandBase(const ParamList& params, const ArgList& args, const FlagList& flags, const std::string& cmdSymbol, const CmdFunc func) : 
		CommandBaseCore(params, args, flags, cmdSymbol, func) {}
};

// return command bases
class RetCommandBase : public CommandBaseCore<lit::LiteralValue*>
{
public:
	RetCommandBase() : CommandBaseCore() {}
	RetCommandBase(const std::string& cmdSymbol, const CmdFunc func) : CommandBaseCore(cmdSymbol, func) {}
	RetCommandBase(const ParamList& params, const ArgList& args, const FlagList& flags, const std::string& cmdSymbol, const CmdFunc func) :
		CommandBaseCore(params, args, flags, cmdSymbol, func) {}
};