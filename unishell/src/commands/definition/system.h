#pragma once

#include "def.h"

#include "../../commands/cmdcore/cmd.h"
#include "../../environment/identifier/idformat.h"
#include "../../filesystem/formating/formating.h"
#include "../../system/system.h"
#include "../../system/settings/settings.h"
#include "../../system/settings/option_format.h"
#include "../../data/litvalue/obj_predef.h"
#include "../../parser/processing/token/token_processing.h"
#include "../../system/memory/memfree.h"


extern void __run_block(const lit::Block&, bool free_cmd = true);


// exp
START_COMMAND(SysCmdExp, {}, CommandBase, "exp", CmdFunc::System)
void exec() override {}
END_COMMAND


// do
START_COMMAND(SysCmdDo, ParamVec({ {nullptr, {lit::LitType::Block}} }), CommandBase, "do", CmdFunc::System)
void exec() override
{
	__run_block(asBlock(args[0]));
}
END_COMMAND



// if
START_COMMAND(SysCmdIf, ParamVec({ {nullptr, {lit::LitType::Bool}}, {nullptr, {lit::LitType::Block}}, {lit::lit(lit::Block()), {lit::LitType::Block}} }), CommandBase, "if", CmdFunc::System)
void exec() override
{
	if (asBool(args[0]))
		__run_block(asBlock(args[1]));

	else if (!asBlock(args[2]).empty())
		__run_block(asBlock(args[2]));
}
END_COMMAND

// while
START_COMMAND(SysCmdWhile, ParamVec({ {nullptr, {lit::LitType::Literal}}, {nullptr, {lit::LitType::Block}} }), CommandBase, "while", CmdFunc::System)
void exec() override
{
	const TokenList pre = InstreamScanner(asStr(args[0])).scanTokens();
	lit::LiteralValue* condition;

	while (asBool((condition = TokenProcess::process(pre)[0].getLiteral()))) {
		__run_block(asBlock(args[1]), false);
		delete condition;
	}
}
END_COMMAND



// print
START_COMMAND(SysCmdPrint, { lit::lit(std::string("")) }, CommandBase, "print", CmdFunc::System)
void exec() override {
	for (lit::LiteralValue* value : args)
		sysprint(litToStr(value));

	if (!flags.hasFlag("nl"))
		sysprintln("");
}
END_COMMAND

// clear
START_COMMAND(SysCmdClear, {}, CommandBase, "clear", CmdFunc::System)
void exec() override {
	system("cls");
}
END_COMMAND



// sys
START_COMMAND(SysCmdSys, ParamVec({ {nullptr, {lit::LitType::Literal}} }), CommandBase, "sys", CmdFunc::System)
void exec() override {
	const std::string cmdline = "cd " + __workingPath->getPath() + " & " + asStr(args[0]);

	system(cmdline.c_str());
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




// listOpts
START_COMMAND(SysCmdListOpts, ParamVec({ { lit::lit(-1), {lit::LitType::Number} } }), CommandBase, "listOpts", CmdFunc::System)
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

// setOpt
START_COMMAND(SysCmdSetOpt, ParamVec({ {nullptr, {lit::LitType::Number}}, {nullptr, {lit::LitType::Any}} }), CommandBase, "setOpt", CmdFunc::System)
void exec() override {
	const int optionIndex = (int)asDbl(args[0]);

	Option* option = __settings->getOption((size_t)optionIndex);

	if (!option)
		THROW_RUNTIME_ERR("Couldn't find option with index: " + numformat(tostr(optionIndex)));

	try {
		option->setValue(args[1]);
	}
	catch (Option::InvalidValueTypeErr err) {
		if (!err.expectedColorString)
			THROW_RUNTIME_ERR(lit::getTypeAsString(option->types(), true) + " expected, got " + lit::getTypeAsString(err.value->type(), true));
		else
			THROW_RUNTIME_ERR("Valid Color Structure String expected");
	}
}
END_COMMAND



// appStat
START_COMMAND(SysCmdAppStat, {}, CommandBase, "appStat", CmdFunc::System)
void exec() override {
	sysprintln(std::string("Name: ") + qtd(UNISHLL_NAME));
	sysprintln(std::string("System: ") + qtd(UNISHLL_OS));

	sysprintln("");
	sysprintln("Settings JSON Data File Load Failed: " + lit::boolToString(__sys_stat->settingJsonFileLoadFailed, true));
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



// sysMemStat
START_COMMAND(SysRetCmdSysMemStat, {}, RetCommandBase, "sysMemStat", CmdFunc::System)
lit::LiteralValue* exec() override {
	return lit::newSysMemStatObj(getSystemMemoryInfo());
}
END_COMMAND

// sysDiskStat
START_COMMAND(SysRetCmdSysDiskStat, {}, RetCommandBase, "sysDiskStat", CmdFunc::System)
lit::LiteralValue* exec() override {
	return lit::newSysDiskStatObj(getSystemDiskInfo());
}
END_COMMAND