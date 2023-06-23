#pragma once

#include "def.h"

#include "../../commands/cmdcore/cmd.h"
#include "../../environment/identifier/idformat.h"
#include "../../filesystem/formating/formating.h"
#include "../../system/system.h"
#include "../../system/settings/option_format.h"

// print
START_COMMAND(SysCmdPrint, { lit::lit(std::string("")) }, CommandBase, "print", CmdFunc::System)
void exec() override {
	for (lit::LiteralValue* value : args)
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
START_COMMAND(SysCmdCd, ParamVec({ {nullptr, {lit::LitType::Literal}} }), CommandBase, "cd", CmdFunc::System)
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
START_COMMAND(SysCmdVar, ParamVec({ {nullptr, {lit::LitType::Literal}},	nullptr }), CommandBase, "var", CmdFunc::System)
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
		FormatedIdentifierData data = formatIdentifier(identifier);

		sysprintln(formatedIdentifierDataToString(data));
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
START_COMMAND(SysCmdCmdHelp, ParamVec({ {lit::lit(""), {lit::LitType::Literal}} }), CommandBase, "cmdHelp", CmdFunc::System)
void exec() override {
	std::string cmdName = asStr(args[0]);

	if (!cmdName.empty()) {
		CommandBase* pCmd = getCommand(cmdName);

		if (!pCmd)
			THROW_RUNTIME_ERR("Unknown command: " + clr(cmdName, __clr_command->toString()));

		std::string msg = stringifyHelpData(pCmd->help());
		sysprintln(msg);
	}

	else sysprintln(getAllCmdHelpMessage(flags.hasFlag("nm")));
}
END_COMMAND

// retCmdHelp
START_COMMAND(SysCmdRetCmdHelp, ParamVec({ {lit::lit(""), {lit::LitType::Literal}} }), CommandBase, "retCmdHelp", CmdFunc::System)
void exec() override {
	std::string cmdName = asStr(args[0]);

	if (!cmdName.empty()) {
		RetCommandBase* pCmd = getRetCommand(cmdName);

		if (!pCmd)
			THROW_RUNTIME_ERR("Unknown command: " + clr(cmdName, __clr_command->toString()));

		std::string msg = stringifyHelpData(pCmd->help());
		sysprintln(msg);
	}

	else sysprintln(getAllRetCmdHelpMessage(flags.hasFlag("nm")));
}
END_COMMAND



// clrHelp
START_COMMAND(SysCmdClrHelp, {}, CommandBase, "clrHelp", CmdFunc::System)
void exec() override {
	sysprintln(getColoredColorList());
}
END_COMMAND

// idClrHelp
START_COMMAND(SysCmdIdColorHelp, {}, CommandBase, "idClrHelp", CmdFunc::System)
void exec() override {
	sysprintln(getColoredIdColorList());
}
END_COMMAND

// clrModeHelp
START_COMMAND(SysCmdClrModeHelp, {}, CommandBase, "clrModeHelp", CmdFunc::System)
void exec() override {
	sysprintln(getColoredColorModeList());
}
END_COMMAND




// opts
START_COMMAND(SysCmdOpts, { lit::lit(-1) }, CommandBase, "opts", CmdFunc::System)
void exec() override {
	const int index = (int)asDbl(args[0]);
	int currentOptionIndex = 0;

	if (index != -1) {
		Option* option = __settings->getOption((size_t)index);

		if (!option)
			THROW_RUNTIME_ERR("Couldn't find option with index: " + numformat(tostr(index)));

		sysprintln(formatOption(*option));
		return;
	}

	for (const Section& section : __settings->getAllSections())
		sysprintln(formatSection(section, currentOptionIndex));
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
lit::LiteralValue* exec() override {
	std::string input;
	std::getline(std::cin, input);

	return lit::lit(input);
}
END_COMMAND