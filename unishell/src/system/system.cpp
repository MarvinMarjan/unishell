#include "system.h"

bool System::abort = false;

System::System()
{
	addSysId("NAME",	lit::lit("unishell"));
	addSysId("OS",		lit::lit("Windows"));
}


Identifier* System::getEnvId(const std::string& idName, const int index)
{
	Identifier* identifier = __environment->getId(idName);

	if (!identifier)
		throw SystemException(EnvironmentError, "Unknown indentifier: " + idformat(idName),
			(index != -1) ? ExceptionRef(*__userInput, index) : ExceptionRef(""));

	return identifier;
}


void System::delEnvId(const std::string& idName)
{
	if (__environment->exists(idName) && !__environment->isSysId(idName))
		__environment->delId(idName);
	else if (!__environment->isSysId(idName))
		throw SystemException(EnvironmentError, "Unknown identifier: " + idformat(idName));
	else
		throw SystemException(EnvironmentError, "Can't delete system identifiers.");
}