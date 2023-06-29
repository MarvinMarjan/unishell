#include "src/system/system.h"
#include "src/commands/cmdcore/cmd.h"
#include "src/parser/processing/token/token_processing.h"
#include "src/instream/input/instream.h"
#include "src/instream/scanner/instream_scanner.h"



static void __run(TokenList input) {
	// empty
	if (!input.size())
		return;

	FlagList flags = getFlags(input);
	removeFlags(input);

	ArgList args = getArgs(input);
	CommandBase* command = getCommand(input[0].getLexical(), args, flags);

	// unknown command
	if (!command)
		throw new CommandErr("Unknown command: " + clr(input[0].getLexical(), __clr_command->toString()));

	// execute command
	command->exec();
}



// runs from user input
void __repl_entry_mode()
{
	// main loop
	while (!System::getAbort()) {
		try {
			sysprint(clr(__workingPath->getPath(), 41) + clr(" $ ", 127));
			*System::input() = INStream::getLine(); // sets global user input

			TokenList input = TokenProcess::process(InstreamScanner(UNISHLL_USER_INPUT).scanTokens());

			__run(input);
		}

		// system exception was thrown
		catch (UserException* sysErr) {
			System::error(sysErr);
		}

		// unhandled exception
		catch (...) {
			System::error(Exception("unknown", "Unexpected error"));
		}
	}
}


// runs from a file
void __fread_entry_mode(const std::string& fpath)
{
	setCursorVisible(true);

	if (!fsys::File::exists(fpath)) {
		System::error(new FilesysErr("Couldn't open file: " + qtd(fpath)));
		return;
	}

	const std::string fContent = fsys::File::readAsString(fpath);

	std::vector<TokenList> lines = InstreamScanner::separateLinesFromTokens(InstreamScanner(fContent, AddEndlTokens).scanTokens());

	size_t currentExecution = 0;

	for (const TokenList& line : lines) {
		currentExecution++;

		try {
			__run(TokenProcess::process(line));
		}
		catch (Exception* err) {
			System::error(err);
			sysprintln("Line: " + tostr(line[0].getLine()));
			return;
		}
	}
}