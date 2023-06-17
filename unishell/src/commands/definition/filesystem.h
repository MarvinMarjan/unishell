#pragma once

#include "def.h"

// createFile
START_COMMAND(FSysCmdCreateFile, ParamVec({ {nullptr, {lit::LitType::Literal}} }), CommandBase, "createFile", CmdFunc::Filesystem)
void exec() override {
	const PathHandler::PathOperationData res = (*__workingPath) << asStr(args[0]);

	try {
		fsys::File::createFile(res.path);
	}
	catch (const fsys::FileException& err) {
		THROW_RUNTIME_ERR("Couldn't create file at: " + qtd(err.path));
	}
}
END_COMMAND

// removeFile
START_COMMAND(FSysCmdRemoveFile, ParamVec({ {nullptr, {lit::LitType::Literal}} }), CommandBase, "removeFile", CmdFunc::Filesystem)
void exec() override {
	const PathHandler::PathOperationData res = (*__workingPath) + asStr(args[0]);

	checkPath(res, asStr(args[0]), symbol);
	checkPathType(res.path, ExpFile, symbol);

	fsys::File::removeFile(res.path);
}
END_COMMAND

// createDir
START_COMMAND(FSysCmdCreateDir, ParamVec({ {nullptr, {lit::LitType::Literal}} }), CommandBase, "createDir", CmdFunc::Filesystem)
void exec() override {
	const PathHandler::PathOperationData res = (*__workingPath) << asStr(args[0]);

	try {
		fsys::File::createDir(res.path);
	}
	catch (const fsys::FileException& err) {
		THROW_RUNTIME_ERR("Couldn't create dir at: " + err.path);
	}
}
END_COMMAND

// removeDir
START_COMMAND(FSysCmdRemoveDir, ParamVec({ {nullptr, {lit::LitType::Literal}} }), CommandBase, "removeDir", CmdFunc::Filesystem)
void exec() override {
	const PathHandler::PathOperationData res = (*__workingPath) + asStr(args[0]);

	checkPath(res, asStr(args[0]), symbol);
	checkPathType(res.path, ExpDir, symbol);

	fsys::File::removeDir(res.path);
}
END_COMMAND



// RETCOMMANDS




// getFileData
START_COMMAND(FSysRetCmdGetFileData, ParamVec({ {nullptr, {lit::LitType::Literal}} }), RetCommandBase, "getFileData", CmdFunc::Filesystem)
lit::LiteralValue* exec() override {
	const PathHandler::PathOperationData res = (*__workingPath) + asStr(args[0]);

	checkPath(res, asStr(args[0]), symbol);
	checkPathType(res.path, ExpFile, symbol);

	return fsys::File::getFileDataObjFromFile(res.path);
}
END_COMMAND

// getDirEntryName
START_COMMAND(FSysRetCmdGetDirEntryName, ParamVec({ {nullptr, {lit::LitType::Literal}} }), RetCommandBase, "getDirEntryName", CmdFunc::Filesystem)
lit::LiteralValue* exec() override {
	const PathHandler::PathOperationData res = (*__workingPath) + asStr(args[0]);

	checkPath(res, asStr(args[0]), symbol);
	checkPathType(res.path, ExpDir, symbol);

	return lit::lit(alg::vector::map<FileEntry, lit::LiteralValue*>(fsys::File::fileList(res.path), [](FileEntry file) {
		return lit::lit(file.path().filename().string());
	}));
}
END_COMMAND

// getDirEntryData
START_COMMAND(FSysRetCmdGetDirEntryData, ParamVec({ {nullptr, {lit::LitType::Literal}} }), RetCommandBase, "getDirEntryData", CmdFunc::Filesystem)
lit::LiteralValue* exec() override {
	const PathHandler::PathOperationData res = (*__workingPath) + asStr(args[0]);

	checkPath(res, asStr(args[0]), symbol);
	checkPathType(res.path, ExpDir, symbol);

	return lit::lit(alg::vector::map<FileEntry, lit::LiteralValue*>(fsys::File::fileList(res.path), [](FileEntry file) {
		return fsys::File::getFileDataObjFromFile(file.path().string());
	}));
}
END_COMMAND

// exists
START_COMMAND(FSysRetCmdExists, ParamVec({ {nullptr, {lit::LitType::Literal}} }), RetCommandBase, "exists", CmdFunc::Filesystem)
lit::LiteralValue* exec() override {
	const PathHandler::PathOperationData res = (*__workingPath) << asStr(args[0]);

	return lit::lit(fsys::File::exists(res.path));
}
END_COMMAND



// read
START_COMMAND(FSysRetCmdRead, ParamVec({ {nullptr, {lit::LitType::Literal}} }), RetCommandBase, "read", CmdFunc::Filesystem)
lit::LiteralValue* exec() override {
	PathHandler::PathOperationData res = (*__workingPath) + asStr(args[0]);

	checkPath(res, asStr(args[0]), symbol);
	checkPathType(res.path, ExpFile, symbol);

	try {
		return lit::lit(fsys::File::readAsString(res.path));
	}
	catch (const fsys::FileException& err) {
		THROW_RUNTIME_ERR("Couldn't open file: " + qtd(err.path));
	}
}
END_COMMAND

// readAsList
START_COMMAND(FSysRetCmdReadAsList, ParamVec({ {nullptr, {lit::LitType::Literal}} }), RetCommandBase, "readAsList", CmdFunc::Filesystem)
lit::LiteralValue* exec() override {
	PathHandler::PathOperationData res = (*__workingPath) + asStr(args[0]);

	checkPath(res, asStr(args[0]), symbol);
	checkPathType(res.path, ExpFile, symbol);

	try {
		return lit::lit(lit::stringListToLiteralList(fsys::File::readAsList(res.path)));
	}
	catch (const fsys::FileException& err) {
		THROW_RUNTIME_ERR("Couldn't open file: " + qtd(err.path));
	}
}
END_COMMAND

// write
START_COMMAND(FSysRetCmdWrite, ParamVec({ {nullptr, {lit::LitType::Literal}}, {nullptr, {lit::LitType::Literal}}, {lit::lit(false), {lit::LitType::Bool}} }), RetCommandBase, "write", CmdFunc::Filesystem)
lit::LiteralValue* exec() override {
	PathHandler::PathOperationData res = (*__workingPath) + asStr(args[0]);
	bool appendMode = asBool(args[2]);

	checkPath(res, asStr(args[0]), symbol);
	checkPathType(res.path, ExpFile, symbol);

	fsys::File::write(res.path, asStr(args[1]), (appendMode) ? std::ios::app : std::ios::out);

	return lit::lit(fsys::File::readAsString(res.path));
}
END_COMMAND