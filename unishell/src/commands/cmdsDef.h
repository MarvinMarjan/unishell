#pragma once

#include "../system/system.h"
#include "../base/commandBaseCore.h"
#include "../utilities/typeUtil.h"

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


#define THROW_RUNTIME_ERR(msg) throw SystemException(CommandRuntimeError, msg)





// print
START_COMMAND(CmdPrint, { litStr(std::string("")) }, CommandBase, "print")
	void exec() override {
		for (LiteralValue* value : args)
			sysprint(litToStr(value));

		sysprintln("");
	}
END_COMMAND


// var
START_COMMAND(CmdVar, ParamVec({ nullptr, nullptr }), CommandBase, "var")
	void exec() override {
		System::env()->addId(Identifier(litToStr(args[0]), args[1]));
	}
END_COMMAND 

// del
START_COMMAND(CmdDel, { nullptr }, CommandBase, "del")
	void exec() override {
		System::delEnvId(litToStr(args[0]));
	}
END_COMMAND


// exit
START_COMMAND(CmdExit, {}, CommandBase, "exit")
	void exec() override {
		System::exit();
	}
END_COMMAND



// ***---------- RETCOMMANDS ----------***



// type
START_COMMAND(RetCmdType, { nullptr }, RetCommandBase, "type")
	LiteralValue* exec() override {
		return litStr(TypeUtil::getTypeAsString(getValueType(args[0])));
	}
END_COMMAND


// size
START_COMMAND(RetCmdSize, ParamVec({ {nullptr, {Literal, List}} }), RetCommandBase, "size")
	LiteralValue* exec() override {
		IdValueType type = getValueType(args[0]);

		if (type == Literal) return litNum((double)asStr(args[0]).size());
		if (type == List) return litNum((double)asList(args[0]).size());

		return nullptr;
	}
END_COMMAND


// at
START_COMMAND(RetCmdAt, ParamVec({ {nullptr, {Literal, List}}, {nullptr, {Number}} }), RetCommandBase, "at")
	LiteralValue* exec() override
	{
		IdValueType type = getValueType(args[0]);

		LiteralValue* src = args[0];
		int index = (int)asDbl(args[1]);

		if (type == Literal) {
			checkIndex(index, asStr(src).size());
			return litStr(StringUtil::charToStr(asStr(src).at(index)));
		}

		if (type == List) {
			checkIndex(index, asList(src).size());
			return asList(src).at(index);
		}

		return nullptr;
	}

	private:
		static inline void checkIndex(int index, size_t max) {
			if (index >= max || index < 0)
				THROW_RUNTIME_ERR("Invalid index: " + numformat(tostr(index)));
		}
END_COMMAND


// split
START_COMMAND(RetCmdSplit, ParamVec({ {nullptr, {Literal}}, {litStr(" "), {Literal}} }), RetCommandBase, "split")
	LiteralValue* exec() override {
		if (asStr(args[1]).size() > 1)
			THROW_RUNTIME_ERR("Single character literal expected: " + qtd(asStr(args[1])));

		LiteralValue* list = litList({});
		
		for (const std::string& item : StringUtil::split(asStr(args[0]), asStr(args[1])[0]))
			asList(list).push_back(litStr(item));

		return list;
	}
END_COMMAND

inline ArgList getArgs(TokenList input, bool encapsulate = true, bool firstIsCommand = true, bool* hasExplicitList = nullptr) {
	size_t index = (firstIsCommand) ? 1 : 0;

	if (input.size() <= index) return ArgList(); // has no args

	if (encapsulate) {
		size_t i = index;
		for (i; i < input.size(); i++) {}
		return ArgList(TokenList(input.begin() + index, input.begin() + i));
	}

	else if (input[index].getType() == LIST) {
		if (hasExplicitList != nullptr)
			*hasExplicitList = true;

		return ArgList(input[index]);
	}

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
	CHECK_CMD(RetCmdAt);
	CHECK_CMD(RetCmdSplit);

	return nullptr;
}
