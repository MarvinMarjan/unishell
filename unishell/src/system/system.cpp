#include "system.h"

bool System::abort = false;

System::System()
{
	addSysId("NAME",	lit("unishell"));
	addSysId("OS",		lit("Windows"));
}