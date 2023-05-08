#include <iostream>

#include "src/system/system.h"
#include "src/instream/instream.h"

int main(int argc, char** argv)
{
	System sys;

	sys.setCursorVisible(false);

	while (true) {
		std::string aux = INStream::getLine();

		sysprintln("inputed text: " + clr(aux, green));
	}
}