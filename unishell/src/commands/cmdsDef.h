#pragma once

#include "../system/system.h"
#include "../base/commandBaseCore.h"
#include "../utilities/typeUtil.h"
#include "../outstream/outputControl.h"

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


static inline void checkIndex(int index, size_t max, const std::string& symbol) {
	if (index >= max || index < 0)
		THROW_RUNTIME_ERR("Invalid index: " + numformat(tostr(index)));
}

static inline void checkIndex(LiteralValue * obj, const std::string& key, const std::string& symbol) {
	if (asObj(obj).find(key) == asObj(obj).end())
		THROW_RUNTIME_ERR("Invalid property: " + qtd(key));
}



// print
START_COMMAND(CmdPrint, { litStr(std::string("")) }, CommandBase, "print")
	void exec() override {
		for (LiteralValue* value : args)
			sysprint(litToStr(value));

		sysprintln("");
	}
END_COMMAND


// clear
START_COMMAND(CmdClear, {}, CommandBase, "clear")
	void exec() override {
		system("cls");
	}
END_COMMAND


// cd
START_COMMAND(CmdCd, ParamVec({ {nullptr, {Literal}} }), CommandBase, "cd")
	void exec() override {
		PathHandler* sysp = System::path();
		
		const std::string path = asStr(args[0]);

		if (!sysp->manip(PathScanner(path).scanTokens()))
			THROW_RUNTIME_ERR("Invalid path: " + qtd(path));
	}
END_COMMAND


// ls
START_COMMAND(CmdLs, {}, CommandBase, "ls")
	void exec() override {
		FileList list = FileUtil::fileList(System::path()->getPath());

		for (const FileEntry& file : list) {
			sysprintln(FileUtil::formatFileEntryAsString(file));
		}
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



// input
START_COMMAND(RetCmdInput, {}, RetCommandBase, "input");
	LiteralValue* exec() override {
		std::string input;
		std::getline(std::cin, input);

		return litStr(input);
	}
END_COMMAND



// type
START_COMMAND(RetCmdType, { nullptr }, RetCommandBase, "type")
	LiteralValue* exec() override {
		return litStr(TypeUtil::getTypeAsString(getValueType(args[0])));
	}
END_COMMAND


// size
START_COMMAND(RetCmdSize, ParamVec({ {nullptr, {Literal, List, Object}} }), RetCommandBase, "size")
	LiteralValue* exec() override {
		IdValueType type = getValueType(args[0]);

		if (type == Literal) return litNum((double)asStr(args[0]).size());
		if (type == List) return litNum((double)asList(args[0]).size());
		if (type == Object) return litNum((double)asObj(args[0]).size());

		return nullptr;
	}
END_COMMAND


// at
START_COMMAND(RetCmdAt, ParamVec({ {nullptr, {Literal, List, Object}}, {nullptr, {Number, Literal}} }), RetCommandBase, "at")
	LiteralValue* exec() override
	{
		IdValueType srcType = getValueType(args[0]);
		IdValueType indexType = getValueType(args[1]);

		if ((srcType == Literal || srcType == List) && indexType != Number)
			THROW_RUNTIME_ERR("Number expected for Literal | List");

		else if (srcType == Object && indexType != Literal)
			THROW_RUNTIME_ERR("Literal expected for Object");

		LiteralValue* src = args[0];
		std::string key = "";
		int index = -1;

		
		if (srcType == Literal || srcType == List)
			index = (int)asDbl(args[1]);

		else if (srcType == Object)
			key = asStr(args[1]);


		if (srcType == Literal) {
			checkIndex(index, asStr(src).size(), symbol);
			return litStr(StringUtil::charToStr(asStr(src).at(index)));
		}

		if (srcType == List) {
			checkIndex(index, asList(src).size(), symbol);
			return asList(src).at(index);
		}

		if (srcType == Object) {
			checkIndex(src, key, symbol);
			return asObj(src).at(key);
		}

		return nullptr;
	}
END_COMMAND

// sub
START_COMMAND(RetCmdSub, ParamVec({ {nullptr, {Literal}}, {nullptr, {Number}}, {nullptr, {Number}} }), RetCommandBase, "sub")
	LiteralValue* exec() override {
		std::string src = asStr(args[0]);
		int begin = (int)asDbl(args[1]);
		int end = (int)asDbl(args[2]);

		checkIndex(begin, src.size(), symbol);
		checkIndex(end, src.size(), symbol);

		return litStr(src.substr(begin, end + 1 - begin));
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

// append
START_COMMAND(RetCmdAppend, ParamVec({ {nullptr, {List}}, {nullptr} }), RetCommandBase, "append")
	LiteralValue* exec() override {
		if (args[0]->type() == List)
			for (size_t i = 1; i < args.size(); i++)
				asList(args[0]).push_back(args[i]);

		return args[0];
	}
END_COMMAND

// insert
START_COMMAND(RetCmdInsert, ParamVec({ {nullptr, {Object}}, {nullptr, {Literal}}, {nullptr} }), RetCommandBase, "insert")
	LiteralValue* exec() override {
		asObj(args[0]).insert({ asStr(args[1]), args[2] });

		return args[0];
	}
END_COMMAND;

// erase
START_COMMAND(RetCmdErase, ParamVec({ {nullptr, {List, Literal}}, {nullptr, {Number}}, {nullptr, {Number}} }), RetCommandBase, "erase")
	LiteralValue* exec() override {
		LiteralValue* src = args[0];
		int begIndex = (int)asDbl(args[1]), endIndex = (int)asDbl(args[2]);
		int current = 0;

		if (src->type() == List) {
			checkIndex(begIndex, asList(src).size(), symbol);
			checkIndex(endIndex, asList(src).size(), symbol);

			LiteralValueList* list = &asList(src);
			list->erase(list->begin() + begIndex, list->begin() + endIndex + 1);
		}

		else if (src->type() == Literal) {
			checkIndex(begIndex, asStr(src).size(), symbol);
			checkIndex(endIndex, asStr(src).size(), symbol);

			std::string* str = &asStr(src);
			str->erase(str->begin() + begIndex, str->begin() + endIndex + 1);
		}

		return args[0];
	}
END_COMMAND

// eraseAt
START_COMMAND(RetCmdEraseAt, ParamVec({ {nullptr, {List, Object}}, {nullptr, {Number, Literal}} }), RetCommandBase, "eraseAt")
	LiteralValue* exec() override {
		LiteralValue* src = args[0];
		LiteralValue* at = args[1];

		if (src->type() == List) {
			if (at->type() != Number)
				THROW_RUNTIME_ERR("Number expected for List: " + litToStr(at));

			int index = (int)asDbl(at);

			checkIndex(index, asList(src).size(), symbol);

			asList(src).erase(asList(src).begin() + index);
		}

		else if (src->type() == Object) {
			if (at->type() != Literal)
				THROW_RUNTIME_ERR("Literal expected for Object: " + litToStr(at));

			std::string key = asStr(at);

			checkIndex(src, key, symbol);

			asObj(src).erase(key);
		}

		return args[0];
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
