#include <iostream>

#include "src/system/system.h"
#include "src/instream/instream.h"

#include "src/parser/instream/instrScanner.h"

#include "src/parser/expression/exprASTPrinter.h"
#include "src/parser/expression/exprParser.h"

#include "src/utilities/fileUtil.h"

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
			
			TokenList input = InstreamScanner(*sys.input()).scanTokens();

			if (input[0].getLexical() == "ast")
				sysprintln(asStr(ExprASTPrinter().print(ExprParser(input[1].getSub(), *sys.input()).parse())));

			else if (input[0].getLexical() == "tokens")
				for (size_t i = 1; i < input.size(); i++)
					sysprintln(input[i].getLexical() + " - " + std::to_string((int)input[i].getType()));

			else if (input[0].getLexical() == "print" && input[1].getLiteral())
				sysprintln(TypeUtil::literalValueToString(input[1].getLiteral()));

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