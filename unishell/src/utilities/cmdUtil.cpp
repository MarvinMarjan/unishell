#include "cmdUtil.h"

#include "../commands/definition/cmds.h"

CommandBase* CmdUtil::getCommand(const std::string& cmdName)
{
	CHECK_CMD_P(SysCmdPrint);
	CHECK_CMD_P(SysCmdClear);
		 
	CHECK_CMD_P(SysCmdCd);
	CHECK_CMD_P(SysCmdLs);
	CHECK_CMD_P(FSysCmdCreateFile);
	CHECK_CMD_P(FSysCmdCreateDir);
	CHECK_CMD_P(FSysCmdRemoveFile);
	CHECK_CMD_P(FSysCmdRemoveDir);
			 
	CHECK_CMD_P(SysCmdVar);
	CHECK_CMD_P(SysCmdDel);
	CHECK_CMD_P(SysCmdEnv);
			 
	CHECK_CMD_P(SysCmdHelp);
	CHECK_CMD_P(SysCmdCmdHelp);
	CHECK_CMD_P(SysCmdRetCmdHelp);
	CHECK_CMD_P(SysCmdClrHelp);
	CHECK_CMD_P(SysCmdIdColorHelp);
	CHECK_CMD_P(SysCmdClrModeHelp);
			 
	CHECK_CMD_P(SysCmdExit);

	return nullptr;
}

RetCommandBase* CmdUtil::getRetCommand(const std::string& cmdName)
{
	CHECK_CMD_P(SysRetCmdInput);
	CHECK_CMD_P(SysRetCmdType);

	CHECK_CMD_P(LiteralRetCmdSize);
	CHECK_CMD_P(LiteralRetCmdAt);
	CHECK_CMD_P(LiteralRetCmdErase);
	CHECK_CMD_P(LiteralRetCmdSub);
	CHECK_CMD_P(LiteralRetCmdSplit);
	CHECK_CMD_P(LiteralRetCmdJoin);

	CHECK_CMD_P(ListRetCmdAt);
	CHECK_CMD_P(ListRetCmdSize);
	CHECK_CMD_P(ListRetCmdAppend);
	CHECK_CMD_P(ListRetCmdErase);
	CHECK_CMD_P(ListRetCmdEraseAt);

	CHECK_CMD_P(ObjectRetCmdAt);
	CHECK_CMD_P(ObjectRetCmdSize);
	CHECK_CMD_P(ObjectRetCmdInsert);
	CHECK_CMD_P(ObjectRetCmdEraseAt);

	CHECK_CMD_P(FSysRetCmdGetFileData);
	CHECK_CMD_P(FSysRetCmdGetDirEntryName);
	CHECK_CMD_P(FSysRetCmdGetDirEntryData);
	CHECK_CMD_P(FSysRetCmdExists);
	CHECK_CMD_P(FSysRetCmdRead);
	CHECK_CMD_P(FSysRetCmdReadAsList);
	CHECK_CMD_P(FSysRetCmdWrite);

	CHECK_CMD_P(RegexRetCmdMatch);
	CHECK_CMD_P(RegexRetCmdReplace);

	CHECK_CMD_P(TypeRetCmdLiteral);
	CHECK_CMD_P(TypeRetCmdNumber);
	CHECK_CMD_P(TypeRetCmdBool);

	CHECK_CMD_P(NumberRetCmdRound);
	CHECK_CMD_P(NumberRetCmdIsDecimal);

	return nullptr;
}

CommandBase* CmdUtil::getCommand(const std::string& cmdName, ArgList args, FlagList flags)
{
	CHECK_CMD(SysCmdPrint);
	CHECK_CMD(SysCmdClear);

	CHECK_CMD(SysCmdCd);
	CHECK_CMD(SysCmdLs);
	CHECK_CMD(FSysCmdCreateFile);
	CHECK_CMD(FSysCmdCreateDir);
	CHECK_CMD(FSysCmdRemoveFile);
	CHECK_CMD(FSysCmdRemoveDir);

	CHECK_CMD(SysCmdVar);
	CHECK_CMD(SysCmdDel);
	CHECK_CMD(SysCmdEnv);

	CHECK_CMD(SysCmdHelp);
	CHECK_CMD(SysCmdCmdHelp);
	CHECK_CMD(SysCmdRetCmdHelp);
	CHECK_CMD(SysCmdClrHelp);
	CHECK_CMD(SysCmdIdColorHelp);
	CHECK_CMD(SysCmdClrModeHelp);

	CHECK_CMD(SysCmdExit);

	return nullptr;
}

RetCommandBase* CmdUtil::getRetCommand(const std::string& cmdName, ArgList args, FlagList flags)
{
	CHECK_CMD(SysRetCmdInput);
	CHECK_CMD(SysRetCmdType);

	CHECK_CMD(LiteralRetCmdSub);
	CHECK_CMD(LiteralRetCmdSplit);
	CHECK_CMD(LiteralRetCmdJoin);

	CHECK_CMD(ListRetCmdAppend);

	CHECK_CMD(ObjectRetCmdInsert);

	CHECK_CMD(FSysRetCmdGetFileData);
	CHECK_CMD(FSysRetCmdGetDirEntryName);
	CHECK_CMD(FSysRetCmdGetDirEntryData);
	CHECK_CMD(FSysRetCmdExists);
	CHECK_CMD(FSysRetCmdRead);
	CHECK_CMD(FSysRetCmdReadAsList);
	CHECK_CMD(FSysRetCmdWrite);

	CHECK_CMD(RegexRetCmdMatch);
	CHECK_CMD(RegexRetCmdReplace);

	CHECK_CMD(TypeRetCmdLiteral);
	CHECK_CMD(TypeRetCmdNumber);
	CHECK_CMD(TypeRetCmdBool);

	CHECK_CMD(NumberRetCmdRound);
	CHECK_CMD(NumberRetCmdIsDecimal);



	CHECK_CMD_OL("at", LiteralRetCmdAt, ListRetCmdAt, ObjectRetCmdAt);
	CHECK_CMD_OL("erase", LiteralRetCmdErase, ListRetCmdErase);
	CHECK_CMD_OL("eraseAt", ListRetCmdEraseAt, ObjectRetCmdEraseAt);
	CHECK_CMD_OL("size", ObjectRetCmdSize, ListRetCmdSize, LiteralRetCmdSize);

	return nullptr;
}