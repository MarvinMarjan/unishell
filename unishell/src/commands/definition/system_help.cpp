#include "system.h"


// exp
START_HELP(SysCmdExp)
return { .name = SysCmdExp().symbol, .params = {{"Expr", {lit::LitType::Any}, true}}, .undefinedParamSize = true, .description = "execute the expression ^0 or more."};
END_HELP

// do
START_HELP(SysCmdDo)
return { .name = SysCmdDo().symbol, .params = {{"Block", {lit::LitType::Block}}}, .description = "execute the block ^0." };
END_HELP



// if
START_HELP(SysCmdIf)
return { .name = SysCmdIf().symbol, .params = {{"Condition", {lit::LitType::Bool}}, {"ThenBlock", {lit::LitType::Block}, true}, {"ElseBlock", {lit::LitType::Block}, true}}, .description = "if ^0 is true, execute ^1 block, else, execute ^2 block." };
END_HELP

// while
START_HELP(SysCmdWhile)
return { .name = SysCmdWhile().symbol, .params = {{"Condition", {lit::LitType::Bool}}, {"Block", {lit::LitType::Block}}}, .description = "executes block ^1 while ^0 is true" };
END_HELP



// print
START_HELP(SysCmdPrint)
return { .name = SysCmdPrint().symbol, .params = {{ "Text", {lit::LitType::Any}, true}}, .undefinedParamSize = true, .description = "prints ^0 in console.", .flags = {{"nl", "no-newline"}}};
END_HELP

// clear
START_HELP(SysCmdClear)
return { .name = SysCmdClear().symbol, .description = "clears the entire console screen." };
END_HELP



// sys
START_HELP(SysCmdSys)
return { .name = SysCmdSys().symbol, .params = {{"Source", {lit::LitType::Literal}}}, .description = "executes ^0 as a operational system command." };
END_HELP



// cd
START_HELP(SysCmdCd)
return { .name = SysCmdCd().symbol, .params = {{"Path", {lit::LitType::Literal}}}, .description = "working path manipulation." };
END_HELP

// ls
START_HELP(SysCmdLs)
return { .name = SysCmdLs().symbol, .description = "list all files in current directory." };
END_HELP





// var
START_HELP(SysCmdVar)
return { .name = SysCmdVar().symbol, .params = {{"Name", {lit::LitType::Literal}}, {"Value", {lit::LitType::Any}}}, .description = "creates a variable called ^0 that stores ^1." };
END_HELP

// del
START_HELP(SysCmdDel)
return { .name = SysCmdDel().symbol, .params = {{"Name", {lit::LitType::Literal}}}, .description = "deletes a variable called ^0." };
END_HELP

// env
START_HELP(SysCmdEnv)
return { .name = SysCmdEnv().symbol, .description = "show a list of all system identifiers." };
END_HELP



// help
START_HELP(SysCmdHelp)
return { .name = SysCmdHelp().symbol, .description = "displays a help message." };
END_HELP

// cmdHelp
START_HELP(SysCmdCmdHelp)
return { .name = SysCmdCmdHelp().symbol, .description = "displays a help message describing every command.", .flags = {{"nm", "name"}} };
END_HELP

// retCmdHelp
START_HELP(SysCmdRetCmdHelp)
return { .name = SysCmdRetCmdHelp().symbol, .description = "displays a help message describing every return command.", .flags = {{"nm", "name"}} };
END_HELP

// colorHelp
START_HELP(SysCmdClrHelp)
return { .name = SysCmdClrHelp().symbol, .description = "displays a help message that shows all predefined colors." };
END_HELP

// idClrHelp
START_HELP(SysCmdIdColorHelp)
return { .name = SysCmdIdColorHelp().symbol, .description = "displays a help message that shows all valid color ids." };
END_HELP

// clrModeHelp
START_HELP(SysCmdClrModeHelp)
return { .name = SysCmdClrModeHelp().symbol, .description = "displays a help message that shows all valid color modes." };
END_HELP



// getOpts
START_HELP(SysCmdListOpts)
return { .name = SysCmdListOpts().symbol, .description = "displays a list of all options."};
END_HELP

// setOpt
START_HELP(SysCmdSetOpt)
return { .name = SysCmdSetOpt().symbol, .description = "modifies the value of an option" };
END_HELP



// appStat
START_HELP(SysCmdAppStat)
return { .name = SysCmdAppStat().symbol, .description = "displays some application status" };
END_HELP



// exit
START_HELP(SysCmdExit)
return { .name = SysCmdExit().symbol, .description = "quit unishell." };
END_HELP








// input
START_HELP(SysRetCmdInput)
return { .name = SysRetCmdInput().symbol, .description = "returns the user input." };
END_HELP



// sysMemStat
START_HELP(SysRetCmdSysMemStat)
return { .name = SysRetCmdSysMemStat().symbol, .description = "returns a object containing information about system memory." };
END_HELP

// sysDiskStat
START_HELP(SysRetCmdSysDiskStat)
return { .name = SysRetCmdSysDiskStat().symbol, .description = "returns a object containing information about system disk." };
END_HELP
