#include "system.h"

#include "../utilities/stringUtil.h"

bool System::abort = false;

System::System()
{
	addSysId("__name__", new LiteralValue((std::string)"unishell"));
	addSysId("__newl__", new LiteralValue((std::string)"\n"));
}