#include "system.h"

#include "../utilities/stringUtil.h"

bool System::abort = false;

PathHandler* System::GLOBAL_workingPath = new PathHandler(StringUtil::wstringToString(WindowsSystem::getSystemDesktopPath()) + '/');
std::string* System::GLOBAL_userInput = new std::string();
Environment* System::GLOBAL_environment = new Environment();

System::System()
{
	addSysId("__name__", new LiteralValue((std::string)"unishell"));
	addSysId("__newl__", new LiteralValue((std::string)"\n"));
}