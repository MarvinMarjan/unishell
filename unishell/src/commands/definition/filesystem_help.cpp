#include "filesystem.h"

// createFile
START_HELP(FSysCmdCreateFile)
return { .name = FSysCmdCreateFile().symbol, .params = {{"File", {lit::LitType::Literal}}}, .description = "creates a file." };
END_HELP

// removeFile
START_HELP(FSysCmdRemoveFile)
return { .name = FSysCmdRemoveFile().symbol, .params = {{"File", {lit::LitType::Literal}}}, .description = "remove a file." };
END_HELP

// createDir
START_HELP(FSysCmdCreateDir)
return { .name = FSysCmdCreateDir().symbol, .params = {{"Dir", {lit::LitType::Literal}}}, .description = "creates a directory." };
END_HELP

// removeDir
START_HELP(FSysCmdRemoveDir)
return { .name = FSysCmdRemoveDir().symbol, .params = {{"Dir", {lit::LitType::Literal}}}, .description = "removes a directory." };
END_HELP



// RETCOMMANDS




// getFileData
START_HELP(FSysRetCmdGetFileData)
return { .name = FSysRetCmdGetFileData().symbol, .params = {{"Path", {lit::LitType::Literal}}},
			.description = "returns an Object containing data of file located at ^0." };
END_HELP

// getDirEntryName
START_HELP(FSysRetCmdGetDirEntryName)
return { .name = FSysRetCmdGetDirEntryName().symbol, .params = {{"Path", {lit::LitType::Literal}}},
			.description = "returns a List containing every file name in directory ^0." };
END_HELP

// getDirEntryData
START_HELP(FSysRetCmdGetDirEntryData)
return { .name = FSysRetCmdGetDirEntryData().symbol, .params = {{"Path", {lit::LitType::Literal}}},
			.description = "returns a List containing Objects with data of every file in directory ^0." };
END_HELP

// exists
START_HELP(FSysRetCmdExists)
return { .name = FSysRetCmdExists().symbol, .params = {{"Path", {lit::LitType::Literal}}},
			.description = "returns true if ^0 exists, false otherwise." };
END_HELP

// read
START_HELP(FSysRetCmdRead)
return { .name = FSysRetCmdRead().symbol, .params = {{"File", {lit::LitType::Literal}}},
			.description = "returns the content of ^0." };
END_HELP

// readAsList
START_HELP(FSysRetCmdReadAsList)
return { .name = FSysRetCmdReadAsList().symbol, .params = {{"File", {lit::LitType::Literal}}},
			.description = "returns the content of ^0 as a List." };
END_HELP

// write
START_HELP(FSysRetCmdWrite)
return { .name = FSysRetCmdWrite().symbol, .params = {{"File", {lit::LitType::Literal}}, {"Text", {lit::LitType::Literal}}, {"AppendMode", {lit::LitType::Bool}, true}},
			.description = "writes Text into ^0. if ^2 is true, writes ^1 in the end of ^0."
							"\n\tif ^2 is false, clears ^0 content and writes ^1." };
END_HELP