#include "cmdUtil.h"

#include "../commands/definition/cmdsDef.h"

CommandBase* CmdUtil::getCommand(const std::string& cmdName)
{
	CHECK_CMD_P(CmdPrint);
	CHECK_CMD_P(CmdClear);
			 
	CHECK_CMD_P(CmdCd);
	CHECK_CMD_P(CmdLs);
	CHECK_CMD_P(CmdCreateFile);
	CHECK_CMD_P(CmdCreateDir);
	CHECK_CMD_P(CmdRemoveFile);
	CHECK_CMD_P(CmdRemoveDir);
			 
	CHECK_CMD_P(CmdVar);
	CHECK_CMD_P(CmdDel);
	CHECK_CMD_P(CmdEnv);
			 
	CHECK_CMD_P(CmdHelp);
	CHECK_CMD_P(CmdCmdHelp);
	CHECK_CMD_P(CmdRetCmdHelp);
	CHECK_CMD_P(CmdClrHelp);
	CHECK_CMD_P(CmdIdColorHelp);
	CHECK_CMD_P(CmdClrModeHelp);
			 
	CHECK_CMD_P(CmdExit);

	return nullptr;
}

RetCommandBase* CmdUtil::getRetCommand(const std::string& cmdName)
{
	CHECK_CMD_P(RetCmdInput);

	CHECK_CMD_P(RetCmdType);
	CHECK_CMD_P(RetCmdSize);

	CHECK_CMD_P(RetCmdAt);
	CHECK_CMD_P(RetCmdSub);
	CHECK_CMD_P(RetCmdSplit);
	CHECK_CMD_P(RetCmdJoin);

	CHECK_CMD_P(RetCmdAppend);
	CHECK_CMD_P(RetCmdInsert);
	CHECK_CMD_P(RetCmdErase);
	CHECK_CMD_P(RetCmdEraseAt);

	CHECK_CMD_P(RetCmdGetFileData);
	CHECK_CMD_P(RetCmdGetDirEntryName);
	CHECK_CMD_P(RetCmdGetDirEntryData);
	CHECK_CMD_P(RetCmdExists);
	CHECK_CMD_P(RetCmdRead);
	CHECK_CMD_P(RetCmdReadAsList);
	CHECK_CMD_P(RetCmdWrite);

	CHECK_CMD_P(RetCmdMatch);
	CHECK_CMD_P(RetCmdReplace);

	CHECK_CMD_P(RetCmdLiteral);
	CHECK_CMD_P(RetCmdNumber);
	CHECK_CMD_P(RetCmdRound);
	CHECK_CMD_P(RetCmdIsDecimal);
	CHECK_CMD_P(RetCmdBool);

	return nullptr;
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
	CHECK_CMD(CmdEnv);

	CHECK_CMD(CmdHelp);
	CHECK_CMD(CmdCmdHelp);
	CHECK_CMD(CmdRetCmdHelp);
	CHECK_CMD(CmdClrHelp);
	CHECK_CMD(CmdIdColorHelp);
	CHECK_CMD(CmdClrModeHelp);

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
	CHECK_CMD(RetCmdReadAsList);
	CHECK_CMD(RetCmdWrite);

	CHECK_CMD(RetCmdMatch);
	CHECK_CMD(RetCmdReplace);

	CHECK_CMD(RetCmdLiteral);
	CHECK_CMD(RetCmdNumber);
	CHECK_CMD(RetCmdRound);
	CHECK_CMD(RetCmdIsDecimal);
	CHECK_CMD(RetCmdBool);

	return nullptr;
}