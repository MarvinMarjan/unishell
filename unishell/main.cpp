#include "src/instream/input/instream.h"

#include "src/instream/scanner/instreamScanner.h"

#include "src/parser/processing/token/tokenProcessing.h"

#include "src/expression/AST/exprASTPrinter.h"
#include "src/expression/parser/exprParser.h"

#include "src/filesystem/handle/file.h"

#include "src/utilities/cmdUtil.h"
#include "src/commands/definition/cmds.h"


#include <chrono>


int main(int argc, char** argv)
{



	// disable command line caret
	WindowsSystem::setCursorVisible(false);

	System sys;
	PathHandler* sysPath = sys.path();
	Environment* sysEnv = sys.env();

	// main loop
	while (!sys.getAbort()) {
		try {
			sysprint(clr(sysPath->getPath(), 41) + clr(" $ ", 127));
			*sys.input() = INStream::getLine(); // sets global user input
			
			TokenList input = TokenProcess::process(InstreamScanner(USER_INPUT).scanTokens());

			// empty
			if (!input.size())
				continue;

			FlagList flags = CmdUtil::getFlags(input);
			input = CmdUtil::removeFlags(input);

			ArgList args = CmdUtil::getArgs(input);
			CommandBase* command = CmdUtil::getCommand(input[0].getLexical(), args, flags);

			// unknown command
			if (!command)
				throw SystemException(CommandError, "Unknown command: " + clr(input[0].getLexical(), __clr_command->toString()));

			// execute command
			command->exec();
		}

		// system exception was thrown
		catch (const SystemException& sysErr) {
			sys.error(sysErr);
		}

		// unhandled exception
		catch (...) {
			sys.error(SystemException(InternalSystemError, "Unexpected error"));
		}
	}
}