#include "cmdUtil.h"

#include "../commands/definition/cmdsDef.h"

std::string CmdUtil::getAllCmdHelpMessage(bool nameOnly)
{
	std::string msg = "";

	msg += stringifyHelpData(CmdPrint::help(), __clr_command, nameOnly) + ((!nameOnly) ? "\n\n\n" : "\n");
	msg += stringifyHelpData(CmdClear::help(), __clr_command, nameOnly) + ((!nameOnly) ? "\n\n\n" : "\n");

	msg += stringifyHelpData(CmdCd::help(), __clr_command, nameOnly) + ((!nameOnly) ? "\n\n\n" : "\n");
	msg += stringifyHelpData(CmdLs::help(), __clr_command, nameOnly) + ((!nameOnly) ? "\n\n\n" : "\n");
	msg += stringifyHelpData(CmdCreateFile::help(), __clr_command, nameOnly) + ((!nameOnly) ? "\n\n\n" : "\n");
	msg += stringifyHelpData(CmdRemoveFile::help(), __clr_command, nameOnly) + ((!nameOnly) ? "\n\n\n" : "\n");
	msg += stringifyHelpData(CmdCreateDir::help(), __clr_command, nameOnly) + ((!nameOnly) ? "\n\n\n" : "\n");
	msg += stringifyHelpData(CmdRemoveDir::help(), __clr_command, nameOnly) + ((!nameOnly) ? "\n\n\n" : "\n");

	msg += stringifyHelpData(CmdVar::help(), __clr_command, nameOnly) + ((!nameOnly) ? "\n\n\n" : "\n");
	msg += stringifyHelpData(CmdDel::help(), __clr_command, nameOnly) + ((!nameOnly) ? "\n\n\n" : "\n");

	msg += stringifyHelpData(CmdHelp::help(), __clr_command, nameOnly) + ((!nameOnly) ? "\n\n\n" : "\n");
	msg += stringifyHelpData(CmdCmdHelp::help(), __clr_command, nameOnly) + ((!nameOnly) ? "\n\n\n" : "\n");
	msg += stringifyHelpData(CmdRetCmdHelp::help(), __clr_command, nameOnly) + ((!nameOnly) ? "\n\n\n" : "\n");

	msg += stringifyHelpData(CmdExit::help(), __clr_command, nameOnly) + ((!nameOnly) ? "\n\n\n" : "\n");

	return msg;
}

std::string CmdUtil::getAllRetCmdHelpMessage(bool nameOnly)
{
	std::string msg = "";

	msg += stringifyHelpData(RetCmdInput::help(), __clr_sys_ret_command, nameOnly) + ((!nameOnly) ? "\n\n\n" : "\n");
	msg += stringifyHelpData(RetCmdType::help(), __clr_sys_ret_command, nameOnly) + ((!nameOnly) ? "\n\n\n" : "\n");
	msg += stringifyHelpData(RetCmdSize::help(), __clr_sys_ret_command, nameOnly) + ((!nameOnly) ? "\n\n\n" : "\n");
	msg += stringifyHelpData(RetCmdAt::help(), __clr_sys_ret_command, nameOnly) + ((!nameOnly) ? "\n\n\n" : "\n");
	msg += stringifyHelpData(RetCmdSub::help(), __clr_sys_ret_command, nameOnly) + ((!nameOnly) ? "\n\n\n" : "\n");
	msg += stringifyHelpData(RetCmdSplit::help(), __clr_sys_ret_command, nameOnly) + ((!nameOnly) ? "\n\n\n" : "\n");
	msg += stringifyHelpData(RetCmdJoin::help(), __clr_sys_ret_command, nameOnly) + ((!nameOnly) ? "\n\n\n" : "\n");
	msg += stringifyHelpData(RetCmdAppend::help(), __clr_sys_ret_command, nameOnly) + ((!nameOnly) ? "\n\n\n" : "\n");
	msg += stringifyHelpData(RetCmdInsert::help(), __clr_sys_ret_command, nameOnly) + ((!nameOnly) ? "\n\n\n" : "\n");
	msg += stringifyHelpData(RetCmdErase::help(), __clr_sys_ret_command, nameOnly) + ((!nameOnly) ? "\n\n\n" : "\n");
	msg += stringifyHelpData(RetCmdEraseAt::help(), __clr_sys_ret_command, nameOnly) + ((!nameOnly) ? "\n\n\n" : "\n");
	msg += stringifyHelpData(RetCmdGetFileData::help(), __clr_sys_ret_command, nameOnly) + ((!nameOnly) ? "\n\n\n" : "\n");
	msg += stringifyHelpData(RetCmdGetDirEntryName::help(), __clr_sys_ret_command, nameOnly) + ((!nameOnly) ? "\n\n\n" : "\n");
	msg += stringifyHelpData(RetCmdGetDirEntryData::help(), __clr_sys_ret_command, nameOnly) + ((!nameOnly) ? "\n\n\n" : "\n");
	msg += stringifyHelpData(RetCmdExists::help(), __clr_sys_ret_command, nameOnly) + ((!nameOnly) ? "\n\n\n" : "\n");
	msg += stringifyHelpData(RetCmdRead::help(), __clr_sys_ret_command, nameOnly) + ((!nameOnly) ? "\n\n\n" : "\n");
	msg += stringifyHelpData(RetCmdWrite::help(), __clr_sys_ret_command, nameOnly) + ((!nameOnly) ? "\n\n\n" : "\n");
	msg += stringifyHelpData(RetCmdLiteral::help(), __clr_sys_ret_command, nameOnly) + ((!nameOnly) ? "\n\n\n" : "\n");
	msg += stringifyHelpData(RetCmdNumber::help(), __clr_sys_ret_command, nameOnly) + ((!nameOnly) ? "\n\n\n" : "\n");
	msg += stringifyHelpData(RetCmdBool::help(), __clr_sys_ret_command, nameOnly) + ((!nameOnly) ? "\n\n\n" : "\n");

	return msg;
}



CommandBase* CmdUtil::getCommand(const std::string& cmdName, ArgList args, FlagList flags)
{
	CHECK_CMD(CmdPrint);
	CHECK_CMD(CmdClear);

	CHECK_CMD(CmdCd);
	CHECK_CMD(CmdLs);
	CHECK_CMD(CmdCreateFile);
	CHECK_CMD(CmdCreateDir);
	CHECK_CMD(CmdRemoveFile);
	CHECK_CMD(CmdRemoveDir);

	CHECK_CMD(CmdVar);
	CHECK_CMD(CmdDel);

	CHECK_CMD(CmdHelp);
	CHECK_CMD(CmdCmdHelp);
	CHECK_CMD(CmdRetCmdHelp);

	CHECK_CMD(CmdExit);

	return nullptr;
}

RetCommandBase* CmdUtil::getRetCommand(const std::string& cmdName, ArgList args, FlagList flags)
{
	CHECK_CMD(RetCmdInput);

	CHECK_CMD(RetCmdType);
	CHECK_CMD(RetCmdSize);

	CHECK_CMD(RetCmdAt);
	CHECK_CMD(RetCmdSub);
	CHECK_CMD(RetCmdSplit);
	CHECK_CMD(RetCmdJoin);

	CHECK_CMD(RetCmdAppend);
	CHECK_CMD(RetCmdInsert);
	CHECK_CMD(RetCmdErase);
	CHECK_CMD(RetCmdEraseAt);

	CHECK_CMD(RetCmdGetFileData);
	CHECK_CMD(RetCmdGetDirEntryName);
	CHECK_CMD(RetCmdGetDirEntryData);
	CHECK_CMD(RetCmdExists);
	CHECK_CMD(RetCmdRead);
	CHECK_CMD(RetCmdWrite);

	CHECK_CMD(RetCmdLiteral);
	CHECK_CMD(RetCmdNumber);
	CHECK_CMD(RetCmdBool);

	return nullptr;
}