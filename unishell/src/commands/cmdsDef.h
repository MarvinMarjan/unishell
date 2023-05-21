#pragma once

#include "../system/system.h"
#include "../base/commandBase.h"
#include "../utilities/typeUtil.h"

// boilerplate
#define START_COMMAND(name, argSize) \
	class name : public CommandBase \
	{ \
	public: \
		name(ArgList args) : CommandBase(args, argSize) {}


#define END_COMMAND \
	};


// print
START_COMMAND(CmdPrint, 0)
	void exec() override {
		for (LiteralValue* value : args)
			sysprint(TypeUtil::literalValueToString(value));

		sysprintln("");
	}
END_COMMAND


// var
START_COMMAND(CmdVar, 2)
	void exec() override {
		System::env()->addId(Identifier(TypeUtil::literalValueToString(args[0]), args[1]));
	}
END_COMMAND


// exit
START_COMMAND(CmdExit, 0)
	void exec() override {
		System::exit();
	}
END_COMMAND




inline ArgList getArgs(TokenList input) {
	if (input.size() == 1) return ArgList();
	if (input[1].getType() == LIST) return ArgList(input[1]);

	size_t i = 1;

	for (i; i < input.size(); i++) {}

	return ArgList(TokenList(input.begin() + 1, input.begin() + i));
}

inline CommandBase* getCommand(const std::string& cmdName, ArgList args) {
	if (cmdName == "print") return new CmdPrint(args);
	else if (cmdName == "var") return new CmdVar(args);
	else if (cmdName == "exit") return new CmdExit(args);

	return nullptr;
}