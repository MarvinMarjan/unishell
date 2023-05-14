#include <iostream>

#include "src/system/system.h"
#include "src/instream/instream.h"
#include "src/parser/instream/scanner.h"

#include "src/utilities/fileUtil.h"

int main(int argc, char** argv)
{
	WindowsSystem::setCursorVisible(false);

	System sys;
	PathHandler* sysPath = sys.path();

	while (!sys.getAbort()) {
		sysprint(clr(sysPath->getPath(), 41) + clr(" $ ", 127));
		std::string aux = INStream::getLine();

		StringList input = StringUtil::split(aux);

		if (input[0] == "math") {}

		else if (input[0] == "exit") sys.exit();
	}
}