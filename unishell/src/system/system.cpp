#include "system.h"

bool System::abort = false;

System::System()
{
	addSysId("NAME",	lit::lit("unishell"));
	addSysId("OS",		lit::lit("Windows"));
}