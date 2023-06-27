#pragma once

#include "../cmdcore/help_data.h"
#include "../../path/handler/path_handler.h"
#include "../../base/command_base_core.h"

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


#define THROW_RUNTIME_ERR(msg) \
	throw new CommandRuntimeErr("(" + symbol + ") " + msg) \


enum ExpFileType {
	ExpFile,
	ExpDir
};


// check if the index of a list exists
inline void checkIndex(const int index, const size_t max, const std::string& symbol) {
	if (index >= max || index < 0)
		THROW_RUNTIME_ERR("Invalid index: " + numformat(tostr(index)));
}

// check if the key of an object exists
inline void checkIndex(const lit::LitObject& obj, const std::string& key, const std::string& symbol) {
	if (obj.find(key) == obj.end())
		THROW_RUNTIME_ERR("Invalid property: " + qtd(key));
}

// check if path exists
inline void checkPath(const PathHandler::PathOperationData& data, const std::string& argPath, const std::string& symbol) {
	if (!data.success)
		THROW_RUNTIME_ERR("Invalid path: " + qtd(argPath));
}

// checks if the file in the path is of the expected type
inline void checkPathType(const std::string& path, const ExpFileType expected, const std::string& symbol) {
	if ((fs::is_directory(path) && expected == ExpFile) || (!fs::is_directory(path) && expected == ExpDir))
		THROW_RUNTIME_ERR(((expected == ExpFile) ? "File" : "Directory") + " expected at: " + qtd(path));
}