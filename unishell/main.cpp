#include <iostream>

#include "src/system/system.h"
#include "src/instream/instream.h"

#include "src/parser/instream/instrScanner.h"

#include "src/parser/processing/tokenProcessing.h"

#include "src/parser/expression/exprASTPrinter.h"
#include "src/parser/expression/exprParser.h"

#include "src/utilities/fileUtil.h"

#include <time.h>

int main(int argc, char** argv)
{
	// disable command line caret
	WindowsSystem::setCursorVisible(false);

	System sys;
	PathHandler* sysPath = sys.path();
	Environment* sysEnv = sys.env();

	sysEnv->addId(Identifier("name", new LiteralValue(std::string("Marvin"))));

	// main loop
	while (!sys.getAbort()) {
		try {
			sysprint(clr(sysPath->getPath(), 41) + clr(" $ ", 127));
			*sys.input() = INStream::getLine(); // sets global user input
			
			TokenList input = TokenProcess::process(InstreamScanner(*sys.input()).scanTokens());

			if (input[0].getLexical() == "print" && input.size() > 1) {
				for (size_t i = 1; i < input.size(); i++)
					sysprint(TypeUtil::literalValueToString(input[i].getLiteral()));

				sysprintln("");
			}

			else if (input[0].getLexical() == "exit") sys.exit();
		}

		// system exception was thrown
		catch (SystemException sysErr) {
			sys.error(sysErr);
		}

		// unhandled exception
		catch (...) {
			sys.error(SystemException(InternalSystemError, "Unexpected error"));
		}
	}
}