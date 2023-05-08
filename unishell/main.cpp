#include <iostream>

#include "src/system/system.h"
#include "src/instream/instream.h"

int main(int argc, char** argv)
{
	WindowsSystem::setCursorVisible(false);

	System sys;
	PathHandler* sysPath = sys.path();

	while (!sys.getAbort()) {
		sysprint(clr(sysPath->getPath(), 41) + clr(" $ ", 127));
		std::string aux = INStream::getLine();

		if (aux == "back") 
			sysPath->back();
	}
}