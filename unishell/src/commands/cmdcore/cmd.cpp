#include "cmd.h"

#include "../definition/cmds.h"

CommandBase* getCommand(const std::string& cmdName, const ArgList& args, const FlagList& flags)
{
	CHECK_CMD(SysCmdPrint);
	CHECK_CMD(SysCmdClear);

	CHECK_CMD(SysCmdCd);
	CHECK_CMD(SysCmdLs);

	CHECK_CMD(SysCmdVar);
	CHECK_CMD(SysCmdDel);
	CHECK_CMD(SysCmdEnv);

	CHECK_CMD(SysCmdHelp);
	CHECK_CMD(SysCmdCmdHelp);
	CHECK_CMD(SysCmdRetCmdHelp);
	CHECK_CMD(SysCmdClrHelp);
	CHECK_CMD(SysCmdIdColorHelp);
	CHECK_CMD(SysCmdClrModeHelp);

	CHECK_CMD(SysCmdOpts);

	CHECK_CMD(SysCmdExit);


	CHECK_CMD(FSysCmdCreateFile);
	CHECK_CMD(FSysCmdCreateDir);
	CHECK_CMD(FSysCmdRemoveFile);
	CHECK_CMD(FSysCmdRemoveDir);

	return nullptr;
}

RetCommandBase* getRetCommand(const std::string& cmdName, const ArgList& args, const FlagList& flags)
{
	CHECK_CMD(SysRetCmdInput);

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

	CHECK_CMD(TypeRetCmdType);
	CHECK_CMD(TypeRetCmdLiteral);
	CHECK_CMD(TypeRetCmdNumber);
	CHECK_CMD(TypeRetCmdBool);

	CHECK_CMD(NumberRetCmdRound);
	CHECK_CMD(NumberRetCmdIsDecimal);



	// overload
	CHECK_CMD_OL("at", LiteralRetCmdAt, ListRetCmdAt, ObjectRetCmdAt);
	CHECK_CMD_OL("erase", LiteralRetCmdErase, ListRetCmdErase);
	CHECK_CMD_OL("eraseAt", ListRetCmdEraseAt, ObjectRetCmdEraseAt);
	CHECK_CMD_OL("size", ObjectRetCmdSize, ListRetCmdSize, LiteralRetCmdSize);

	return nullptr;
}