#include <iostream>

#include "src/system/system.h"
#include "src/instream/instream.h"

#include "src/parser/instream/instrScanner.h"
#include "src/parser/expression/exprScanner.h"

#include "src/parser/expression/exprASTPrinter.h"
#include "src/parser/expression/exprParser.h"

#include "src/utilities/fileUtil.h"

int main(int argc, char** argv)
{
	WindowsSystem::setCursorVisible(false);

	System sys;
	PathHandler* sysPath = sys.path();

	while (!sys.getAbort()) {
		try {
			sysprint(clr(sysPath->getPath(), 41) + clr(" $ ", 127));
			InputTokenList input = InputScanner(INStream::getLine()).scanTokens();

			if (input[0].getLexical() == "math")
				for (ExprToken token : ExprScanner(input[1].getLexical()).scanTokens())
					sysprintln(token.getLexical());

			else if (input[0].getLexical() == "ast")
				sysprintln(asStr(ExprASTPrinter().print(ExprParser(ExprScanner(input[1].getLexical()).scanTokens()).parse())));

			else if (input[0].getLexical() == "exit") sys.exit();
		}

		catch (SystemException sysErr) {
			sys.error(sysErr);
		}
	}
}