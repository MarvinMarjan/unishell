#pragma once

#include "../commands/cmdcore/params.h"
#include "../commands/cmdcore/flags.h"

#include "../system/global/global.h"

#include "../environment/environment.h"


#define THROW_COMMAND_ERR(msg) \
	throw new CommandErr("(" + cmdSymbol + ") " + msg) \

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

	Regex,
	JSON
};


inline std::string funcToString(const CmdFunc func) noexcept {
	switch (func) {
	case CmdFunc::Type:			return "Type";
	case CmdFunc::Literal:		return "Literal";
	case CmdFunc::Number:		return "Number";
	case CmdFunc::List:			return "List";
	case CmdFunc::Object:		return "Object";
	case CmdFunc::System:		return "System";
	case CmdFunc::Filesystem:	return "Filesystem";
	case CmdFunc::Regex:		return "Regex";
	case CmdFunc::JSON:			return "JSON";

	default: return "unknown";
	}
}

constexpr inline BaseColorStructure* funcToColor(const CmdFunc func) noexcept {
	switch (func) {
	case CmdFunc::Type:			return __clr_type_command;
	case CmdFunc::Literal:		return __clr_literal_command;
	case CmdFunc::Number:		return __clr_number_command;
	case CmdFunc::List:			return __clr_list_command;
	case CmdFunc::Object:		return __clr_object_command;
	case CmdFunc::System:		return __clr_system_command;
	case CmdFunc::Filesystem:	return __clr_filesystem_command;
	case CmdFunc::Regex:		return __clr_regex_command;
	case CmdFunc::JSON:			return __clr_json_command;

	default: return __clr_command;
	}
}


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

	~CommandBaseCore() {
		for (const Param& param : params)
			if (param.getDefaultValue()) {
				delete param.getDefaultValue();
			}
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
			THROW_COMMAND_ERR("Insufficient arguments");
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

	~CommandBase() {
		dynamic_cast<CommandBaseCore*>(this)->~CommandBaseCore();
	}
};

// return command bases
class RetCommandBase : public CommandBaseCore<lit::LiteralValue*>
{
public:
	RetCommandBase() : CommandBaseCore() {}
	RetCommandBase(const std::string& cmdSymbol, const CmdFunc func) : CommandBaseCore(cmdSymbol, func) {}
	RetCommandBase(const ParamList& params, const ArgList& args, const FlagList& flags, const std::string& cmdSymbol, const CmdFunc func) :
		CommandBaseCore(params, args, flags, cmdSymbol, func) {}

	~RetCommandBase() {
		dynamic_cast<CommandBaseCore*>(this)->~CommandBaseCore();
	}
};