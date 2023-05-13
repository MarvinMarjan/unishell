#include <iostream>

#include "src/system/system.h"
#include "src/instream/instream.h"

#include "src/utilities/fileUtil.h"

int main(int argc, char** argv)
{
	WindowsSystem::setCursorVisible(false);

	System sys;
	PathHandler* sysPath = sys.path();

	while (!sys.getAbort()) {
		sysprint(clr(sysPath->getPath(), 41) + clr(" $ ", 127));
		std::string aux = INStream::getLine();
		StringList splited = StringUtil::split(aux);

		if (splited[0] == "back")
			sysPath->back();

		else if (splited[0] == "into" && splited.size() > 1)
			sysPath->into(splited[1]);

		else if (splited[0] == "manip" && splited.size() > 1)
			sysPath->manip(PathScanner(splited[1]).scanTokens());

		else if (splited[0] == "exit")
			sys.exit();
	}
}