#pragma once

#include "defBase.h"

#include "../../utilities/envUtil.h"
#include "../../utilities/clrUtil.h"
#include "../../utilities/cmdUtil.h"
#include "../../filesystem/formating/fileFormatting.h"
#include "../../system/system.h"

// print
START_COMMAND(SysCmdPrint, { lit(std::string("")) }, CommandBase, "print", CmdFunc::System)
void exec() override {
	for (LiteralValue* value : args)
		sysprint(litToStr(value));

	sysprintln("");
}
END_COMMAND

// clear
START_COMMAND(SysCmdClear, {}, CommandBase, "clear", CmdFunc::System)
void exec() override {
	system("cls");
}
END_COMMAND



// cd
START_COMMAND(SysCmdCd, ParamVec({ {nullptr, {Literal}} }), CommandBase, "cd", CmdFunc::System)
void exec() override {
	PathHandler::PathOperationData res = (*__workingPath) + asStr(args[0]);

	checkPath(res, asStr(args[0]), symbol);
	checkPathType(res.path, ExpDir, symbol);

	__workingPath->setPath(res.path);
}
END_COMMAND

// ls
START_COMMAND(SysCmdLs, {}, CommandBase, "ls", CmdFunc::System)
void exec() override {
	FileList list = fsys::File::fileList(System::path()->getPath());

	for (const FileEntry& file : list) {
		sysprintln(fsys::FileF::formatFileEntryAsString(file));
	}
}
END_COMMAND



// var
START_COMMAND(SysCmdVar, ParamVec({ {nullptr, {Literal}},	nullptr }), CommandBase, "var", CmdFunc::System)
void exec() override {
	System::env()->addId(Identifier(litToStr(args[0]), args[1]));
}
END_COMMAND

// del
START_COMMAND(SysCmdDel, { nullptr }, CommandBase, "del", CmdFunc::System)
void exec() override {
	System::delEnvId(litToStr(args[0]));
}
END_COMMAND

// env
START_COMMAND(SysCmdEnv, {}, CommandBase, "env", CmdFunc::System)
void exec() override {
	for (const Identifier& identifier : __environment->getIdList()) {
		EnvUtil::FormatedIdentifierData data = EnvUtil::formatIdentifier(identifier);

		sysprintln(EnvUtil::formatFIDToString(data));
	}
}
END_COMMAND



// help
START_COMMAND(SysCmdHelp, {}, CommandBase, "help", CmdFunc::System)
void exec() override {
	std::stringstream str;

	str << "Enter " << clr("cmdHelp", __clr_system_command->toString()) << " to get a list of commands." << std::endl;
	str << "Enter " << clr("retCmdHelp", __clr_system_command->toString()) << " to get a list of return commands." << std::endl;
	str << "Enter " << clr("colorHelp", __clr_system_command->toString()) << " to get a list of predefined colors." << std::endl;
	str << "Enter " << clr("idClrHelp", __clr_system_command->toString()) << " to get a list of valid color id." << std::endl;
	str << "Enter " << clr("clrModeHelp", __clr_system_command->toString()) << " to get a list of valid color modes.";

	sysprintln(str.str());
}
END_COMMAND

// cmdHelp
START_COMMAND(SysCmdCmdHelp, ParamVec({ {lit(""), {Literal}} }), CommandBase, "cmdHelp", CmdFunc::System)
void exec() override {
	std::string cmdName = asStr(args[0]);

	if (!cmdName.empty()) {
		CommandBase* pCmd = CmdUtil::getCommand(cmdName);

		if (!pCmd)
			THROW_RUNTIME_ERR("Unknown command: " + clr(cmdName, __clr_command->toString()));

		std::string msg = stringifyHelpData(pCmd->help());
		sysprintln(msg);
	}

	else sysprintln(CmdUtil::getAllCmdHelpMessage(flags.hasFlag("nm")));
}
END_COMMAND

// retCmdHelp
START_COMMAND(SysCmdRetCmdHelp, ParamVec({ {lit(""), {Literal}} }), CommandBase, "retCmdHelp", CmdFunc::System)
void exec() override {
	std::string cmdName = asStr(args[0]);

	if (!cmdName.empty()) {
		RetCommandBase* pCmd = CmdUtil::getRetCommand(cmdName);

		if (!pCmd)
			THROW_RUNTIME_ERR("Unknown command: " + clr(cmdName, __clr_command->toString()));

		std::string msg = stringifyHelpData(pCmd->help());
		sysprintln(msg);
	}

	else sysprintln(CmdUtil::getAllRetCmdHelpMessage(flags.hasFlag("nm")));
}
END_COMMAND



// clrHelp
START_COMMAND(SysCmdClrHelp, {}, CommandBase, "clrHelp", CmdFunc::System)
void exec() override {
	sysprintln(ClrUtil::getColoredColorList());
}
END_COMMAND

// idClrHelp
START_COMMAND(SysCmdIdColorHelp, {}, CommandBase, "idClrHelp", CmdFunc::System)
void exec() override {
	sysprintln(ClrUtil::getColoredIdColorList());
}
END_COMMAND

// clrModeHelp
START_COMMAND(SysCmdClrModeHelp, {}, CommandBase, "clrModeHelp", CmdFunc::System)
void exec() override {
	sysprintln(ClrUtil::getColoredColorModeList());
}
END_COMMAND



// exit
START_COMMAND(SysCmdExit, {}, CommandBase, "exit", CmdFunc::System)
void exec() override {
	System::exit();
}
END_COMMAND



// RETCOMMANDS




// input
START_COMMAND(SysRetCmdInput, {}, RetCommandBase, "input", CmdFunc::System);
LiteralValue* exec() override {
	std::string input;
	std::getline(std::cin, input);

	return lit(input);
}
END_COMMAND