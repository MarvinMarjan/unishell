#include "system.h"

#include "../utilities/stringUtil.h"

bool System::abort = false;

System::System()
{
	addSysId("NAME",	lit("unishell"));
	addSysId("OS",		lit("Windows"));
}