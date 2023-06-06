#pragma once

#include "../../system/system.h"
#include "../../base/commandBaseCore.h"
#include "../../outstream/outputControl.h"
#include "../../utilities/typeUtil.h"
#include "../../utilities/cmdUtil.h"
#include "../../utilities/clrUtil.h"
#include "../../filesystem/fileFormatting.h"

#include "../helpData.h"

// boilerplate

// if params have more than one param, then
// you need to explicit ParamVec
#define START_COMMAND(name, params, base, cmdSymbol) \
	class name : public base \
	{ \
	public: \
		name() : base() {} \
		name(ArgList args, FlagList flags) : base({ params }, args, flags, cmdSymbol) {} \
		\
		static inline const std::string symbol = cmdSymbol; \
		CommandHelpData help() override; \
		


#define END_COMMAND \
	}; \


#define CHECK_CMD(cmd) \
	if (cmdName == cmd::symbol) return new cmd(args, flags) \

#define CHECK_CMD_P(cmd) \
	if (cmdName == cmd::symbol) return new cmd() \


#define THROW_RUNTIME_ERR(msg) \
	throw SystemException(CommandRuntimeError, "(" + symbol + ") " + msg) \


enum ExpFileType {
	ExpFile,
	ExpDir
};


// check if the index of a list exists
inline void checkIndex(int index, size_t max, const std::string& symbol) {
	if (index >= max || index < 0)
		THROW_RUNTIME_ERR("Invalid index: " + numformat(tostr(index)));
}

// check if the key of an object exists
inline void checkIndex(LiteralValue* obj, const std::string& key, const std::string& symbol) {
	if (asObj(obj).find(key) == asObj(obj).end())
		THROW_RUNTIME_ERR("Invalid property: " + qtd(key));
}

// check if path exists
inline void checkPath(PathHandler::PathOperationData data, const std::string& argPath, const std::string& symbol) {
	if (!data.success)
		THROW_RUNTIME_ERR("Invalid path: " + qtd(argPath));
}

// checks if the file in the path is of the expected type
inline void checkPathType(const std::string& path, ExpFileType expected, const std::string& symbol) {
	if ((fs::is_directory(path) && expected == ExpFile) || (!fs::is_directory(path) && expected == ExpDir))
		THROW_RUNTIME_ERR(((expected == ExpFile) ? "File" : "Directory") + " expected at: " + qtd(path));
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
	FileList list = fsys::File::fileList(System::path()->getPath());

	for (const FileEntry& file : list) {
		sysprintln(fsys::FileF::formatFileEntryAsString(file));
	}
}
END_COMMAND

// createFile
START_COMMAND(CmdCreateFile, ParamVec({ {nullptr, {Literal}} }), CommandBase, "createFile")
	void exec() override {
		PathHandler::PathOperationData res = (*__workingPath) << asStr(args[0]);

		try {
			fsys::File::createFile(res.path);
		}
		catch (const fsys::FileException& err) {
			THROW_RUNTIME_ERR("Couldn't create file at: " + qtd(err.path));
		}
	}
END_COMMAND

// removeFile
START_COMMAND(CmdRemoveFile, ParamVec({ {nullptr, {Literal}} }), CommandBase, "removeFile")
void exec() override {
	PathHandler::PathOperationData res = (*__workingPath) + asStr(args[0]);

	checkPath(res, asStr(args[0]), symbol);
	checkPathType(res.path, ExpFile, symbol);

	fsys::File::removeFile(res.path);
}
END_COMMAND

// createDir
START_COMMAND(CmdCreateDir, ParamVec({ {nullptr, {Literal}} }), CommandBase, "createDir")
	void exec() override {
		PathHandler::PathOperationData res = (*__workingPath) << asStr(args[0]);

		try {
			fsys::File::createDir(res.path);
		}
		catch (const fsys::FileException& err) {
			THROW_RUNTIME_ERR("Couldn't create dir at: " + err.path);
		}
	}
END_COMMAND

// removeDir
START_COMMAND(CmdRemoveDir, ParamVec({ {nullptr, {Literal}} }), CommandBase, "removeDir")
void exec() override {
	PathHandler::PathOperationData res = (*__workingPath) + asStr(args[0]);

	checkPath(res, asStr(args[0]), symbol);
	checkPathType(res.path, ExpDir, symbol);

	fsys::File::removeDir(res.path);
}
END_COMMAND





// var
START_COMMAND(CmdVar, ParamVec({ {nullptr, {Literal}},	nullptr }), CommandBase, "var")
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





// help
START_COMMAND(CmdHelp, {}, CommandBase, "help")
	void exec() override {
		std::stringstream str;

		str << "Enter " << clr("cmdHelp", __clr_command->toString()) << " to get a list of commands." << std::endl;
		str << "Enter " << clr("retCmdHelp", __clr_command->toString()) << " to get a list of return commands." << std::endl;
		str << "Enter " << clr("colorHelp", __clr_command->toString()) << " to get a list of predefined colors." << std::endl;
		str << "Enter " << clr("idClrHelp", __clr_command->toString()) << " to get a list of valid color id.";

		sysprintln(str.str());
	}
END_COMMAND

// cmdHelp
START_COMMAND(CmdCmdHelp, ParamVec({ {litStr(""), {Literal}} }), CommandBase, "cmdHelp")
	void exec() override {
		std::string cmdName = asStr(args[0]);

		if (!cmdName.empty()) {
			CommandBase* pCmd = CmdUtil::getCommandPointer(cmdName);

			if (!pCmd)
				THROW_RUNTIME_ERR("Unknown command: " + clr(cmdName, __clr_command->toString()));

			std::string msg = stringifyHelpData(pCmd->help());
			sysprintln(msg);
		}

		else sysprintln(CmdUtil::getAllCmdHelpMessage(flags.hasFlag("nm")));
	}
END_COMMAND

// retCmdHelp
START_COMMAND(CmdRetCmdHelp, ParamVec({ {litStr(""), {Literal}} }), CommandBase, "retCmdHelp")
	void exec() override {
		std::string cmdName = asStr(args[0]);

		if (!cmdName.empty()) {
			RetCommandBase* pCmd = CmdUtil::getRetCommandPointer(cmdName);

			if (!pCmd)
				THROW_RUNTIME_ERR("Unknown command: " + clr(cmdName, __clr_sys_ret_command->toString()));

			std::string msg = stringifyHelpData(pCmd->help());
			sysprintln(msg);
		}

		else sysprintln(CmdUtil::getAllRetCmdHelpMessage(flags.hasFlag("nm")));
	}
END_COMMAND

// clrHelp
START_COMMAND(CmdClrHelp, {}, CommandBase, "clrHelp")
	void exec() override {
		sysprintln(ClrUtil::getColoredColorList());
	}
END_COMMAND

// idClrHelp
START_COMMAND(CmdIdColorHelp, {}, CommandBase, "idClrHelp")
void exec() override {
	sysprintln(ClrUtil::getColoredIdColorList());
}
END_COMMAND

// clrModeHelp
START_COMMAND(CmdClrModeHelp, {}, CommandBase, "clrModeHelp")
void exec() override {
	sysprintln(ClrUtil::getColoredColorModeList());
}
END_COMMAND





// exit
START_COMMAND(CmdExit, {}, CommandBase, "exit")
	void exec() override {
		System::exit();
	}
END_COMMAND





// ***----------                RETCOMMANDS                ----------***





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

		return litStr(src.substr(begin, (size_t)end + 1 - begin));
	}
END_COMMAND

// split
START_COMMAND(RetCmdSplit, ParamVec({ {nullptr, {Literal}}, {litStr(" "), {Literal}} }), RetCommandBase, "split")
	LiteralValue* exec() override {
		if (asStr(args[1]).size() > 1)
			THROW_RUNTIME_ERR("Single character Literal expected: " + qtd(asStr(args[1])));

		LiteralValue* list = litList({});
		
		for (const std::string& item : StringUtil::split(asStr(args[0]), asStr(args[1])[0]))
			asList(list).push_back(litStr(item));

		return list;
	}
END_COMMAND

// join
START_COMMAND(RetCmdJoin, ParamVec({ {nullptr, {List}}, { litStr(" "), {Literal}} }), RetCommandBase, "join")
	LiteralValue* exec() override {
		if (!TypeUtil::isListOf(args[0], Literal))
			THROW_RUNTIME_ERR("Only Literal type List accepted: " + litToStr(args[0], true));

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
	LiteralValue* exec() override  {
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





// getFileData
START_COMMAND(RetCmdGetFileData, ParamVec({ {nullptr, {Literal}} }), RetCommandBase, "getFileData")
	LiteralValue* exec() override {
		PathHandler::PathOperationData res = (*__workingPath) + asStr(args[0]);

		checkPath(res, asStr(args[0]), symbol); 
		checkPathType(res.path, ExpFile, symbol);

		return fsys::File::getFileDataObjFromFile(res.path);
	}
END_COMMAND

// getDirEntryName
START_COMMAND(RetCmdGetDirEntryName, ParamVec({ {nullptr, {Literal}} }), RetCommandBase, "getDirEntryName")
	LiteralValue* exec() override {
		PathHandler::PathOperationData res = (*__workingPath) + asStr(args[0]);

		checkPath(res, asStr(args[0]), symbol);
		checkPathType(res.path, ExpDir, symbol);

		return litList(VectorUtil::map<FileEntry, LiteralValue*>(fsys::File::fileList(res.path), [] (FileEntry file) {
			return litStr(file.path().filename().string());
		}));
	}
END_COMMAND

// getDirEntryData
START_COMMAND(RetCmdGetDirEntryData, ParamVec({ {nullptr, {Literal}} }), RetCommandBase, "getDirEntryData")
	LiteralValue* exec() override {
		PathHandler::PathOperationData res = (*__workingPath) + asStr(args[0]);

		checkPath(res, asStr(args[0]), symbol);
		checkPathType(res.path, ExpDir, symbol);

		return litList(VectorUtil::map<FileEntry, LiteralValue*>(fsys::File::fileList(res.path), [](FileEntry file) {
			return fsys::File::getFileDataObjFromFile(file.path().string());
		}));
	}
END_COMMAND

// exists
START_COMMAND(RetCmdExists, ParamVec({ {nullptr, {Literal}} }), RetCommandBase, "exists")
	LiteralValue* exec() override {
		PathHandler::PathOperationData res = (*__workingPath) << asStr(args[0]);

		return litBool(fsys::File::exists(res.path));
	}
END_COMMAND

// read
START_COMMAND(RetCmdRead, ParamVec({ {nullptr, {Literal}} }), RetCommandBase, "read")
	LiteralValue* exec() override {
		PathHandler::PathOperationData res = (*__workingPath) + asStr(args[0]);

		checkPath(res, asStr(args[0]), symbol);
		checkPathType(res.path, ExpFile, symbol);

		try {
			return litStr(fsys::File::readAsString(res.path));
		}
		catch (const fsys::FileException& err) {
			THROW_RUNTIME_ERR("Couldn't open file: " + qtd(err.path));
		}
	}
END_COMMAND

// write
START_COMMAND(RetCmdWrite, ParamVec({ {nullptr, {Literal}}, {nullptr, {Literal}}, {litBool(false), {Bool}} }), RetCommandBase, "write")
	LiteralValue* exec() override {
		PathHandler::PathOperationData res = (*__workingPath) + asStr(args[0]);
		bool appendMode = asBool(args[2]);

		checkPath(res, asStr(args[0]), symbol);
		checkPathType(res.path, ExpFile, symbol);

		fsys::File::write(res.path, asStr(args[1]), (appendMode) ? std::ios::app : std::ios::out);

		return litStr(fsys::File::readAsString(res.path));
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
