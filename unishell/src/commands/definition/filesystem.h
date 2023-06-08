#pragma once

#include "defBase.h"

// createFile
START_COMMAND(FSysCmdCreateFile, ParamVec({ {nullptr, {Literal}} }), CommandBase, "createFile", CmdFunc::Filesystem)
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
START_COMMAND(FSysCmdRemoveFile, ParamVec({ {nullptr, {Literal}} }), CommandBase, "removeFile", CmdFunc::Filesystem)
void exec() override {
	PathHandler::PathOperationData res = (*__workingPath) + asStr(args[0]);

	checkPath(res, asStr(args[0]), symbol);
	checkPathType(res.path, ExpFile, symbol);

	fsys::File::removeFile(res.path);
}
END_COMMAND

// createDir
START_COMMAND(FSysCmdCreateDir, ParamVec({ {nullptr, {Literal}} }), CommandBase, "createDir", CmdFunc::Filesystem)
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
START_COMMAND(FSysCmdRemoveDir, ParamVec({ {nullptr, {Literal}} }), CommandBase, "removeDir", CmdFunc::Filesystem)
void exec() override {
	PathHandler::PathOperationData res = (*__workingPath) + asStr(args[0]);

	checkPath(res, asStr(args[0]), symbol);
	checkPathType(res.path, ExpDir, symbol);

	fsys::File::removeDir(res.path);
}
END_COMMAND



// RETCOMMANDS




// getFileData
START_COMMAND(FSysRetCmdGetFileData, ParamVec({ {nullptr, {Literal}} }), RetCommandBase, "getFileData", CmdFunc::Filesystem)
LiteralValue* exec() override {
	PathHandler::PathOperationData res = (*__workingPath) + asStr(args[0]);

	checkPath(res, asStr(args[0]), symbol);
	checkPathType(res.path, ExpFile, symbol);

	return fsys::File::getFileDataObjFromFile(res.path);
}
END_COMMAND

// getDirEntryName
START_COMMAND(FSysRetCmdGetDirEntryName, ParamVec({ {nullptr, {Literal}} }), RetCommandBase, "getDirEntryName", CmdFunc::Filesystem)
LiteralValue* exec() override {
	PathHandler::PathOperationData res = (*__workingPath) + asStr(args[0]);

	checkPath(res, asStr(args[0]), symbol);
	checkPathType(res.path, ExpDir, symbol);

	return litList(VectorUtil::map<FileEntry, LiteralValue*>(fsys::File::fileList(res.path), [](FileEntry file) {
		return litStr(file.path().filename().string());
		}));
}
END_COMMAND

// getDirEntryData
START_COMMAND(FSysRetCmdGetDirEntryData, ParamVec({ {nullptr, {Literal}} }), RetCommandBase, "getDirEntryData", CmdFunc::Filesystem)
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
START_COMMAND(FSysRetCmdExists, ParamVec({ {nullptr, {Literal}} }), RetCommandBase, "exists", CmdFunc::Filesystem)
LiteralValue* exec() override {
	PathHandler::PathOperationData res = (*__workingPath) << asStr(args[0]);

	return litBool(fsys::File::exists(res.path));
}
END_COMMAND



// read
START_COMMAND(FSysRetCmdRead, ParamVec({ {nullptr, {Literal}} }), RetCommandBase, "read", CmdFunc::System)
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

// readAsList
START_COMMAND(FSysRetCmdReadAsList, ParamVec({ {nullptr, {Literal}} }), RetCommandBase, "readAsList", CmdFunc::System)
LiteralValue* exec() override {
	PathHandler::PathOperationData res = (*__workingPath) + asStr(args[0]);

	checkPath(res, asStr(args[0]), symbol);
	checkPathType(res.path, ExpFile, symbol);

	try {
		return litList(TypeUtil::stringListToLiteralList(fsys::File::readAsList(res.path)));
	}
	catch (const fsys::FileException& err) {
		THROW_RUNTIME_ERR("Couldn't open file: " + qtd(err.path));
	}
}
END_COMMAND

// write
START_COMMAND(FSysRetCmdWrite, ParamVec({ {nullptr, {Literal}}, {nullptr, {Literal}}, {litBool(false), {Bool}} }), RetCommandBase, "write", CmdFunc::System)
LiteralValue* exec() override {
	PathHandler::PathOperationData res = (*__workingPath) + asStr(args[0]);
	bool appendMode = asBool(args[2]);

	checkPath(res, asStr(args[0]), symbol);
	checkPathType(res.path, ExpFile, symbol);

	fsys::File::write(res.path, asStr(args[1]), (appendMode) ? std::ios::app : std::ios::out);

	return litStr(fsys::File::readAsString(res.path));
}
END_COMMAND