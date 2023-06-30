#include "src/instream/input/instream.h"

#include "src/instream/scanner/instream_scanner.h"

#include "src/parser/processing/token/token_processing.h"

#include "src/expression/AST/expr_ast_printer.h"
#include "src/expression/parser/expr_parser.h"

#include "src/filesystem/handle/file.h"

#include "src/commands/definition/cmds.h"

#include "src/algorithm/chrono/meter.h"

#include "src/system/windows/system_memory.h"
#include "src/system/boot/boot.h"



extern void __repl_entry_mode();
extern void __fread_entry_mode(const std::string& fpath);



int main(int argc, char** argv)
{
	Boot boot(argv, argc);
	BootSettings bootConfig;

	try {
		bootConfig = boot.getBootSettings(boot.flags());
	}
	catch (Exception* err) {
		System::error(err);
	}

	// disable command line caret
	setCursorVisible(false);

	System sys;

	
	// entry modes
	if (bootConfig.sourceFile.empty())
		__repl_entry_mode();

	else {
		try {
			__fread_entry_mode(bootConfig.sourceFile);
		}
		catch (UserException* err) {
			System::error(err);
		}
	}



	__settings->updateDataFromOptions();

	__settings->data().save();
	__environment->data().save();
}