#include "cmdsDef.h"

#define START_HELP(cmd) \
	CommandHelpData cmd::help() {

#define END_HELP \
	}

// print
START_HELP(CmdPrint)
return { CmdPrint::symbol, {{"Text", {Any}, true}}, true, "prints Text in console." };
END_HELP

// clear
START_HELP(CmdClear)
return { CmdClear::symbol, {}, false, "clears the entire console screen."};
END_HELP



// cd
START_HELP(CmdCd)
return { CmdCd::symbol, {{"Path", {Literal}, false}}, false, "working path manipulation." };
END_HELP

// ls
START_HELP(CmdLs)
return { CmdLs::symbol, {}, false, "list all files in current directory." };
END_HELP

// createFile
START_HELP(CmdCreateFile)
return { CmdCreateFile::symbol, {{"File", {Literal}, false}}, false, "creates a file." };
END_HELP

// removeFile
START_HELP(CmdRemoveFile)
return { CmdRemoveFile::symbol, {{"File", {Literal}, false}}, false, "remove a file." };
END_HELP

// createDir
START_HELP(CmdCreateDir)
return { CmdCreateDir::symbol, {{"Dir", {Literal}, false}}, false, "creates a directory." };
END_HELP

// removeDir
START_HELP(CmdRemoveDir)
return { CmdRemoveDir::symbol, {{"Dir", {Literal}, false}}, false, "removes a directory." };
END_HELP



// var
START_HELP(CmdVar)
return { CmdVar::symbol, {{"Name", {Literal}, false}, {"Value", {Any}, false}}, false, "creates a variable called Name that stores Value." };
END_HELP

// del
START_HELP(CmdDel)
return { CmdDel::symbol, {{"Name", {Literal}, false}}, false, "deletes a variable called Name." };
END_HELP



// help
START_HELP(CmdHelp)
return { CmdHelp::symbol, {}, false, "displays a help message." };
END_HELP

// cmdHelp
START_HELP(CmdCmdHelp)
return { CmdCmdHelp::symbol, {}, false, "displays a help message describing every command." };
END_HELP

// retCmdHelp
START_HELP(CmdRetCmdHelp)
return { CmdRetCmdHelp::symbol, {}, false, "displays a help message describing every return command." };
END_HELP



// exit
START_HELP(CmdExit)
return { CmdExit::symbol, {}, false, "quit unishell." };
END_HELP








// input
START_HELP(RetCmdInput)
return { RetCmdInput::symbol, {}, false, "returns the user input." };
END_HELP



// type
START_HELP(RetCmdType)
return { RetCmdType::symbol, {{"Value", {Any}, false}}, false, "returns the type of Value." };
END_HELP



// size
START_HELP(RetCmdSize)
return { RetCmdSize::symbol, {{"Value", {Literal, List, Object}, false}}, false, "returns the size of Value." };
END_HELP



// at
START_HELP(RetCmdAt)
return { RetCmdAt::symbol, {{"Value", {Literal, List, Object}, false}, {"Where", {Literal, Number}, false}},
			false, "returns the value inside Value at Where." };
END_HELP

// sub
START_HELP(RetCmdSub)
return { RetCmdSub::symbol, {{"Value", {Literal}, false}, {"Begin", {Number}, false}, {"End", {Number}, false}}, false,
			"returns a sub string between index Begin and End." };
END_HELP

// split
START_HELP(RetCmdSplit)
return { RetCmdSplit::symbol, {{"Value", {Literal}, false}, {"Separator", {Literal}, true}}, false, "splits Value in every Separator (single char)." };
END_HELP

// join
START_HELP(RetCmdJoin)
return { RetCmdJoin::symbol, {{"Source", {List}, false}, {"Separator", {Literal}, true}}, false,
			"joins every value in Source (Literal-only List) separating with Separator and returns the result." };
END_HELP

// append
START_HELP(RetCmdAppend)
return { RetCmdAppend::symbol, {{"Source", {List}, false}, {"Value", {Any}, false}}, false, "appends Value into Source and returns Source." };
END_HELP

// insert
START_HELP(RetCmdInsert)
return { RetCmdInsert::symbol, {{"Source", {Object}, false}, {"Name", {Literal}, false}, {"Value", {Any}, false}}, false,
			"inserts a pair of Name and Value into Source and returns Source." };
END_HELP

// erase
START_HELP(RetCmdErase)
return { RetCmdErase::symbol, {{"Source", {List, Literal}, false}, {"Begin", {Number}, false}, {"End", {Number}, false}}, false,
			"erases values int Source between Begin and End and returns Source." };
END_HELP

// eraseAt
START_HELP(RetCmdEraseAt)
return { RetCmdEraseAt::symbol, {{"Source", {List, Object}, false}, {"Where", {Literal, Number}, false}}, false,
			"erases item at Where location inside Source and returns Source." };
END_HELP



// getFileData
START_HELP(RetCmdGetFileData)
return { RetCmdGetFileData::symbol, {{"Path", {Literal}, false}}, false, "returns an Object containing data of file located at Path." };
END_HELP

// getDirEntryName
START_HELP(RetCmdGetDirEntryName)
return { RetCmdGetDirEntryName::symbol, {{"Path", {Literal}, false}}, false, "returns a List containing every file name in directory Path." };
END_HELP

// getDirEntryData
START_HELP(RetCmdGetDirEntryData)
return { RetCmdGetDirEntryData::symbol, {{"Path", {Literal}, false}}, false,
			"returns a List containing Objects with data of every file in directory Path." };
END_HELP

// exists
START_HELP(RetCmdExists)
return { RetCmdExists::symbol, {{"Path", {Literal}, false}}, false, "returns true if Path exists, false otherwise." };
END_HELP

// read
START_HELP(RetCmdRead)
return { RetCmdRead::symbol, {{"File", {Literal}, false}}, false, "returns the content of File." };
END_HELP

// write
START_HELP(RetCmdWrite)
return { RetCmdWrite::symbol, {{"File", {Literal}, false}, {"Text", {Literal}, false}, {"AppendMode", {Bool}, true}}, false,
			"writes Text into File. if AppendMode is true, writes Text in the end of File."
			"\n\tif AppendMode is false, clears File content and writes Text." };
END_HELP



// literal
START_HELP(RetCmdLiteral)
return { RetCmdLiteral::symbol, {{"Value", {Literal, Number, Bool}, false}}, false, "converts Value into a Literal type." };
END_HELP

// number
START_HELP(RetCmdNumber)
return { RetCmdNumber::symbol, {{"Value", {Literal}, false}}, false, "try to convert Value into a Number type." };
END_HELP

// bool
START_HELP(RetCmdBool)
return { RetCmdBool::symbol, {{"Value", {Literal}, false}}, false, "converts Value into a Bool type." };
END_HELP