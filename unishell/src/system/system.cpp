#include "system.h"

#include "../utilities/stringUtil.h"

bool System::abort = false;

System::System()
{
	addSysId("NAME", new LiteralValue((std::string)"unishell"));
}