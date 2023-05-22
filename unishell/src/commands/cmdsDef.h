#pragma once

#include "../system/system.h"
#include "../base/commandBase.h"
#include "../base/retCommandBase.h"
#include "../utilities/typeUtil.h"

#include <cmath>

// boilerplate

// if params have more than one param, then
// you need to explicit ParamVec
#define START_COMMAND(name, params, base) \
	class name : public base \
	{ \
	public: \
		name(ArgList args) : base({ params }, args) {} \


#define END_COMMAND \
	}; \


#define CHECK_CMD(cmd, symbol) \
	if (cmdName == symbol) return new cmd(args) \


// print
START_COMMAND(CmdPrint, { new LiteralValue(std::string("")) }, CommandBase)
	void exec() override {
		for (LiteralValue* value : args)
			sysprint(litToStr(value));

		sysprintln("");
	}
END_COMMAND


// var
START_COMMAND(CmdVar, ParamVec({ nullptr, nullptr }), CommandBase)
	void exec() override {
		System::env()->addId(Identifier(litToStr(args[0]), args[1]));
	}
END_COMMAND 

// del
START_COMMAND(CmdDel, { nullptr }, CommandBase)
	void exec() override {
		System::delEnvId(litToStr(args[0]));
	}
END_COMMAND


// exit
START_COMMAND(CmdExit, {}, CommandBase)
	void exec() override {
		System::exit();
	}
END_COMMAND

START_COMMAND(RetCmdPi, {}, RetCommandBase)
	LiteralValue* exec() override {
		return new LiteralValue(3.14159);
	}
END_COMMAND

START_COMMAND(RetCmdPlus, ParamVec({nullptr, nullptr}), RetCommandBase)
	LiteralValue* exec() override {
		LiteralValue* sum = new LiteralValue(0.0);
		for (LiteralValue* val : args)
			sum = new LiteralValue(asDbl(sum) + asDbl(val));

		return sum;
	}
END_COMMAND




inline ArgList getArgs(TokenList input, bool encapsulate = true) {
	if (input.size() == 1) return ArgList(); // has no args

	if (encapsulate) {
		size_t i = 1;
		for (i; i < input.size(); i++) {}
		return ArgList(TokenList(input.begin() + 1, input.begin() + i));
	}

	else if (input[1].getType() == LIST)
		return ArgList(input[1]);

	return ArgList();
}

inline CommandBase* getCommand(const std::string& cmdName, ArgList args) {
	CHECK_CMD(CmdPrint, "print");
	CHECK_CMD(CmdVar, "var");
	CHECK_CMD(CmdDel, "del");
	CHECK_CMD(CmdExit, "exit");

	return nullptr;
}
inline RetCommandBase* getRetCommand(const std::string& cmdName, ArgList args) {
	CHECK_CMD(RetCmdPi, "pi");
	CHECK_CMD(RetCmdPlus, "plus");

	return nullptr;
}
