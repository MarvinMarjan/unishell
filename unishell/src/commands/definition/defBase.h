#pragma once

#include "../../system/system.h"
#include "../../base/commandBaseCore.h"
#include "../../outstream/control/controlChars.h"
#include "../../utilities/typeUtil.h"
#include "../../utilities/cmdUtil.h"
#include "../../utilities/clrUtil.h"
#include "../../utilities/envUtil.h"
#include "../../utilities/objUtil.h"
#include "../../filesystem/formating/fileFormatting.h"

#include "../helpData.h"

// boilerplate

#define START_HELP(cmd) \
	CommandHelpData cmd::help() {

#define END_HELP \
	}

// if params have more than one param, then
// you need to explicit ParamVec
#define START_COMMAND(name, params, base, cmdSymbol, cmdFunc) \
	class name : public base \
	{ \
	public: \
		name() : base(cmdSymbol, cmdFunc) {} \
		name(ArgList args, FlagList flags) : base({ params }, args, flags, cmdSymbol, cmdFunc) {} \
		\
		CommandHelpData help() override; \
		


#define END_COMMAND \
	}; \


#define CHECK_CMD(cmd) \
	if (cmdName == cmd().symbol) return new cmd(args, flags) \



#define CHECK_CMD_OL(symbol, ...) \
	if (cmdName == symbol) return CmdUtil::checkArgOverload<__VA_ARGS__>(args, flags) \



#define CHECK_CMD_P(cmd) \
	if (cmdName == cmd().symbol) return new cmd() \


#define THROW_RUNTIME_ERR(msg) \
	throw SystemException(CommandRuntimeError, "(" + symbol + ") " + msg) \


enum ExpFileType {
	ExpFile,
	ExpDir
};


// check if the index of a list exists
constexpr inline void checkIndex(const int index, const size_t max, const std::string& symbol) {
	if (index >= max || index < 0)
		THROW_RUNTIME_ERR("Invalid index: " + numformat(tostr(index)));
}

// check if the key of an object exists
inline void checkIndex(const LitObj& obj, const std::string& key, const std::string& symbol) {
	if (obj.find(key) == obj.end())
		THROW_RUNTIME_ERR("Invalid property: " + qtd(key));
}

// check if path exists
constexpr inline void checkPath(const PathHandler::PathOperationData& data, const std::string& argPath, const std::string& symbol) {
	if (!data.success)
		THROW_RUNTIME_ERR("Invalid path: " + qtd(argPath));
}

// checks if the file in the path is of the expected type
inline void checkPathType(const std::string& path, const ExpFileType expected, const std::string& symbol) {
	if ((fs::is_directory(path) && expected == ExpFile) || (!fs::is_directory(path) && expected == ExpDir))
		THROW_RUNTIME_ERR(((expected == ExpFile) ? "File" : "Directory") + " expected at: " + qtd(path));
}