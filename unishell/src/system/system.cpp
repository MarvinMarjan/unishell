#include "system.h"

#include "../utilities/stringUtil.h"

bool System::abort = false;

PathHandler* System::workingPath = new PathHandler(StringUtil::wstringToString(WindowsSystem::getSystemDesktopPath()) + '/');
