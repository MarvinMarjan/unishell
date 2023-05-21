#pragma once

#include "../system/system.h"
#include "../base/commandBase.h"
#include "../utilities/typeUtil.h"

// boilerplate

// if params have more than one param, then
// you need to explicit ParamVec
#define START_COMMAND(name, params) \
	class name : public CommandBase \
	{ \
	public: \
		name(ArgList args) : CommandBase({ params }, args) {} \


#define END_COMMAND \
	}; \


#define CHECK_CMD(cmd, symbol) \
	if (cmdName == symbol) return new cmd(args) \


// print
START_COMMAND(CmdPrint, { new LiteralValue(std::string("")) })
	void exec() override {
		for (LiteralValue* value : args)
			sysprint(litToStr(value));

		sysprintln("");
	}
END_COMMAND


// var
START_COMMAND(CmdVar, ParamVec({ nullptr, nullptr }))
	void exec() override {
		System::env()->addId(Identifier(litToStr(args[0]), args[1]));
	}
END_COMMAND 

// del
START_COMMAND(CmdDel, { nullptr })
	void exec() override {
		System::delEnvId(litToStr(args[0]));
	}
END_COMMAND


// exit
START_COMMAND(CmdExit, {})
	void exec() override {
		System::exit();
	}
END_COMMAND



inline ArgList getArgs(TokenList input) {
	if (input.size() == 1) return ArgList(); // has no args
	if (input[1].getType() == LIST) return ArgList(input[1]);

	size_t i = 1;

	for (i; i < input.size(); i++) {}

	return ArgList(TokenList(input.begin() + 1, input.begin() + i));
}

inline CommandBase* getCommand(const std::string& cmdName, ArgList args) {
	CHECK_CMD(CmdPrint, "print");
	CHECK_CMD(CmdVar, "var");
	CHECK_CMD(CmdDel, "del");
	CHECK_CMD(CmdExit, "exit");

	return nullptr;
}