#pragma once

#include "../system/system.h"
#include "../base/commandBaseCore.h"
#include "../utilities/typeUtil.h"

#include <cmath>

// boilerplate

// if params have more than one param, then
// you need to explicit ParamVec
#define START_COMMAND(name, params, base, cmdSymbol) \
	class name : public base \
	{ \
	public: \
		name(ArgList args) : base({ params }, args) {} \
		\
		static inline const std::string symbol = cmdSymbol;


#define END_COMMAND \
	}; \


#define CHECK_CMD(cmd) \
	if (cmdName == cmd::symbol) return new cmd(args) \






START_COMMAND(CmdPrint, { new LiteralValue(std::string("")) }, CommandBase, "print")
	void exec() override {
		for (LiteralValue* value : args)
			sysprint(litToStr(value));

		sysprintln("");
	}
END_COMMAND



START_COMMAND(CmdVar, ParamVec({ nullptr, nullptr }), CommandBase, "var")
	void exec() override {
		System::env()->addId(Identifier(litToStr(args[0]), args[1]));
	}
END_COMMAND 


START_COMMAND(CmdDel, { nullptr }, CommandBase, "del")
	void exec() override {
		System::delEnvId(litToStr(args[0]));
	}
END_COMMAND



START_COMMAND(CmdExit, {}, CommandBase, "exit")
	void exec() override {
		System::exit();
	}
END_COMMAND



// ***---------- RETCOMMANDS ----------***

//TODO: add support to RETCOMMAND creation by user



START_COMMAND(RetCmdType, { nullptr }, RetCommandBase, "type")
	LiteralValue* exec() override {
		return new LiteralValue((std::string)TypeUtil::getTypeAsString(getValueType(args[0])));
	}
END_COMMAND


START_COMMAND(RetCmdSize, { nullptr }, RetCommandBase, "size")
	LiteralValue* exec() override {
		IdValueType type = getValueType(args[0]);

		if (type == Literal) return new LiteralValue((double)asStr(args[0]).size());
		if (type == List) return new LiteralValue((double)asList(args[0]).size());

		return nullptr;
	}
END_COMMAND



inline ArgList getArgs(TokenList input, bool encapsulate = true, bool firstIsCommand = true) {
	size_t index = (firstIsCommand) ? 1 : 0;

	if (input.size() <= index) return ArgList(); // has no args

	if (encapsulate) {
		size_t i = index;
		for (i; i < input.size(); i++) {}
		return ArgList(TokenList(input.begin() + index, input.begin() + i));
	}

	else if (input[index].getType() == LIST)
		return ArgList(input[index]);

	return ArgList();
}

inline CommandBase* getCommand(const std::string& cmdName, ArgList args) {
	CHECK_CMD(CmdPrint);
	CHECK_CMD(CmdVar);
	CHECK_CMD(CmdDel);
	CHECK_CMD(CmdExit);

	return nullptr;
}
inline RetCommandBase* getRetCommand(const std::string& cmdName, ArgList args) {
	CHECK_CMD(RetCmdType);
	CHECK_CMD(RetCmdSize);

	return nullptr;
}
