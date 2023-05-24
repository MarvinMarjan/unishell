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
		name(ArgList args) : base({ params }, args, cmdSymbol) {} \
		\
		static inline const std::string symbol = cmdSymbol;


#define END_COMMAND \
	}; \


#define CHECK_CMD(cmd) \
	if (cmdName == cmd::symbol) return new cmd(args) \


#define THROW_RUNTIME_ERR(msg) throw SystemException(CommandRuntimeError, "(" + symbol + ") " + msg)





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

// join
START_COMMAND(RetCmdJoin, ParamVec({ {nullptr, {List}}, { litStr(" "), {Literal}} }), RetCommandBase, "join")
	LiteralValue* exec() override {
		for (LiteralValue* val : asList(args[0]))
			if (getValueType(val) != Literal)
				THROW_RUNTIME_ERR("Only Literal type values accepted: " + litToStr(val, true));

		return litStr(VectorUtil::join(VectorUtil::map<LiteralValue*, std::string>(asList(args[0]), [] (LiteralValue* val) {
			return asStr(val);
		}), asStr(args[1])));
	}
END_COMMAND


// literal
START_COMMAND(RetCmdLiteral, ParamVec({ {nullptr, {Literal, Number, Bool}} }), RetCommandBase, "literal")
	LiteralValue* exec() override {
		return litStr(litToStr(args[0]));
	}
END_COMMAND

// number
START_COMMAND(RetCmdNumber, ParamVec({ {nullptr, {Literal}} }), RetCommandBase, "number")
LiteralValue* exec() override {
	double res;
	
	try {
		res = std::stod(litToStr(args[0]));
	}
	catch (const std::invalid_argument&) {
		THROW_RUNTIME_ERR("Unable to convert: " + qtd(asStr(args[0])));
	}
	catch (const std::out_of_range&) {
		THROW_RUNTIME_ERR("Value too large: " + qtd(asStr(args[0])));
	}

	return litNum(res);
}
END_COMMAND

// bool
START_COMMAND(RetCmdBool, ParamVec({ {nullptr, {Literal}} }), RetCommandBase, "bool")
LiteralValue* exec() override {
	return litBool(TypeUtil::stringToBool(asStr(args[0])));
}
END_COMMAND
