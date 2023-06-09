#include "system.h"

#include "../utilities/stringUtil.h"

bool System::abort = false;

System::System()
{
	addSysId("NAME",	litStr("unishell"));
	addSysId("OS",		litStr("Windows"));
}