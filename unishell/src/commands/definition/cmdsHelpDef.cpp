#include "cmdsDef.h"

#define START_HELP(cmd) \
	CommandHelpData cmd::help() {

#define END_HELP \
	}

// print
START_HELP(CmdPrint)
return { .name = CmdPrint::symbol, .params = {{ "Text", {Any}, true}}, .undefinedParamSize = true, .description = "prints Text in console." };
END_HELP

// clear
START_HELP(CmdClear)
return { .name = CmdClear::symbol, .description = "clears the entire console screen."};
END_HELP



// cd
START_HELP(CmdCd)
return { .name = CmdCd::symbol, .params = {{"Path", {Literal}}}, .description = "working path manipulation." };
END_HELP

// ls
START_HELP(CmdLs)
return { .name = CmdLs::symbol, .description = "list all files in current directory." };
END_HELP

// createFile
START_HELP(CmdCreateFile)
return { .name = CmdCreateFile::symbol, .params = {{"File", {Literal}}}, .description = "creates a file." };
END_HELP

// removeFile
START_HELP(CmdRemoveFile)
return { .name = CmdRemoveFile::symbol, .params = {{"File", {Literal}}}, .description = "remove a file." };
END_HELP

// createDir
START_HELP(CmdCreateDir)
return { .name = CmdCreateDir::symbol, .params = {{"Dir", {Literal}}}, .description = "creates a directory." };
END_HELP

// removeDir
START_HELP(CmdRemoveDir)
return { .name = CmdRemoveDir::symbol, .params = {{"Dir", {Literal}}}, .description = "removes a directory." };
END_HELP



// var
START_HELP(CmdVar)
return { .name = CmdVar::symbol, .params = {{"Name", {Literal}}, {"Value", {Any}}}, .description = "creates a variable called Name that stores Value." };
END_HELP

// del
START_HELP(CmdDel)
return { .name = CmdDel::symbol, .params = {{"Name", {Literal}}}, .description = "deletes a variable called Name." };
END_HELP



// help
START_HELP(CmdHelp)
return { .name = CmdHelp::symbol, .description = "displays a help message." };
END_HELP

// cmdHelp
START_HELP(CmdCmdHelp)
return { .name = CmdCmdHelp::symbol, .description = "displays a help message describing every command.", .flags = {{"nm"}} };
END_HELP

// retCmdHelp
START_HELP(CmdRetCmdHelp)
return { .name = CmdRetCmdHelp::symbol, .description = "displays a help message describing every return command.", .flags = {{"nm"}} };
END_HELP



// exit
START_HELP(CmdExit)
return { .name = CmdExit::symbol, .description = "quit unishell." };
END_HELP








// input
START_HELP(RetCmdInput)
return { .name = RetCmdInput::symbol, .description = "returns the user input." };
END_HELP



// type
START_HELP(RetCmdType)
return { .name = RetCmdType::symbol, .params = {{"Value", {Any}}}, .description = "returns the type of Value." };
END_HELP



// size
START_HELP(RetCmdSize)
return { .name = RetCmdSize::symbol, .params = {{"Value", {Literal, List, Object}}}, .description = "returns the size of Value." };
END_HELP



// at
START_HELP(RetCmdAt)
return { .name = RetCmdAt::symbol, .params = {{"Value", {Literal, List, Object}}, {"Where", {Literal, Number}}},
			.description = "returns the value inside Value at Where." };
END_HELP

// sub
START_HELP(RetCmdSub)
return { .name = RetCmdSub::symbol, .params = {{"Value", {Literal}}, {"Begin", {Number}}, {"End", {Number}}},
			.description = "returns a sub string between index Begin and End." };
END_HELP

// split
START_HELP(RetCmdSplit)
return { .name = RetCmdSplit::symbol, .params = {{"Value", {Literal}}, {"Separator", {Literal}, true}},
			.description = "splits Value in every Separator (single char)." };
END_HELP

// join
START_HELP(RetCmdJoin)
return { .name = RetCmdJoin::symbol, .params = {{"Source", {List}}, {"Separator", {Literal}, true}},
			.description = "joins every value in Source (Literal-only List) separating with Separator and returns the result." };
END_HELP

// append
START_HELP(RetCmdAppend)
return { .name = RetCmdAppend::symbol, .params = {{"Source", {List}}, {"Value", {Any}}},
			.description = "appends Value into Source and returns Source." };
END_HELP

// insert
START_HELP(RetCmdInsert)
return { .name = RetCmdInsert::symbol, .params = {{"Source", {Object}}, {"Name", {Literal}}, {"Value", {Any}}},
			.description = "inserts a pair of Name and Value into Source and returns Source." };
END_HELP

// erase
START_HELP(RetCmdErase)
return { .name = RetCmdErase::symbol, .params = {{"Source", {List, Literal}}, {"Begin", {Number}}, {"End", {Number}}},
			.description = "erases values int Source between Begin and End and returns Source." };
END_HELP

// eraseAt
START_HELP(RetCmdEraseAt)
return { .name = RetCmdEraseAt::symbol, .params = {{"Source", {List, Object}}, {"Where", {Literal, Number}}},
			.description = "erases item at Where location inside Source and returns Source." };
END_HELP



// getFileData
START_HELP(RetCmdGetFileData)
return { .name = RetCmdGetFileData::symbol, .params = {{"Path", {Literal}}},
			.description = "returns an Object containing data of file located at Path." };
END_HELP

// getDirEntryName
START_HELP(RetCmdGetDirEntryName)
return { .name = RetCmdGetDirEntryName::symbol, .params = {{"Path", {Literal}}},
			.description = "returns a List containing every file name in directory Path." };
END_HELP

// getDirEntryData
START_HELP(RetCmdGetDirEntryData)
return { .name = RetCmdGetDirEntryData::symbol, .params = {{"Path", {Literal}}},
			.description = "returns a List containing Objects with data of every file in directory Path." };
END_HELP

// exists
START_HELP(RetCmdExists)
return { .name = RetCmdExists::symbol, .params = {{"Path", {Literal}}},
			.description = "returns true if Path exists, false otherwise." };
END_HELP

// read
START_HELP(RetCmdRead)
return { .name = RetCmdRead::symbol, .params = {{"File", {Literal}}},
			.description = "returns the content of File." };
END_HELP

// write
START_HELP(RetCmdWrite)
return { .name = RetCmdWrite::symbol, .params = {{"File", {Literal}}, {"Text", {Literal}}, {"AppendMode", {Bool}, true}},
			.description = "writes Text into File. if AppendMode is true, writes Text in the end of File."
							"\n\tif AppendMode is false, clears File content and writes Text." };
END_HELP



// literal
START_HELP(RetCmdLiteral)
return { .name = RetCmdLiteral::symbol, .params = {{"Value", {Literal, Number, Bool}}}, .description = "converts Value into a Literal type." };
END_HELP

// number
START_HELP(RetCmdNumber)
return { .name = RetCmdNumber::symbol, .params = {{"Value", {Literal}}}, .description = "try to convert Value into a Number type." };
END_HELP

// bool
START_HELP(RetCmdBool)
return { .name = RetCmdBool::symbol, .params = {{"Value", {Literal}}}, .description = "converts Value into a Bool type." };
END_HELP