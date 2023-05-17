#include "system.h"

#include "../utilities/stringUtil.h"

bool System::abort = false;

PathHandler* System::GLOBAL_workingPath = new PathHandler(StringUtil::wstringToString(WindowsSystem::getSystemDesktopPath()) + '/');
std::string* System::GLOBAL_userInput = new std::string();