#include "global.h"

#include "../environment/environment.h"
#include "../path/pathHandler.h"

#include "system.h"

Environment* __environment = new Environment();
PathHandler* __workingPath = new PathHandler(StringUtil::wstringToString(WindowsSystem::getSystemDesktopPath()) + '/');
std::string* __userInput = new std::string();


const StringList __keywords = {
	"and",
	"or",
	"null"
};

const StringList __boolean = {
	"true",
	"false"
};

const StringList __colormode = {
	"normal",
	"dark",
	"italic",
	"underline",
	"crossed"
};

const StringList __color = {
	"std",
	"red",
	"green",
	"yellow",
	"blue",
	"purple",
	"cyan",
	"white",

	"gray",
	"wred",
	"wgreen",
	"wyellow",
	"wblue",
	"wpurple",
	"wcyan"
};

const StringList __color_formats = {
	"id",
	"rgb",
	"clr"
};

const StringList __sys_commands = {
	"print",
	"clear",
	
	"cd",
	"ls",
	"createFile",
	"createDir",
	"removeFile",
	"removeDir",

	"var",
	"del",

	"help",
	"cmdHelp",
	"retCmdHelp",
	
	"exit"
};

const StringList __sys_ret_commands = {
	"input",

	"type",
	"size",

	"at",
	"sub",
	"split",
	"join",

	"append",
	"insert",
	"erase",
	"eraseAt",

	"getFileData",
	"getDirEntryName",
	"getDirEntryData",
	"exists",
	"read",
	"write",

	"literal",
	"number",
	"bool"
};

const FSExtension __fs_file_extensions_text = {
	{{".txt"},						"Text"},
	{{".asm", ".a51",
	".inc", ".nasm"},				"Assembly"},
	{{".bat", ".cmd"},				"Batch"},
	{{".bf", ".b"},					"Brainfuck"},
	{{".cpp", ".hpp", ".c", 
	".h", ".c++", ".cc", ".cp", 
	".cxx", ".h++", ".hh", ".hxx"}, "C/C++"},
	{{".cs"},						"C#"},
	{{".cmake"},					"CMake"},
	{{".cob", ".cbl", 
	".cobol", ".cpy"},				"Cobol"},
	{{".css"},						"CSS"},
	{{".lisp", ".asd", ".lsp", 
	".l"},							"Lisp"},
	{{".dart"},						"Dart"},
	{{".f", ".f90"},				"Fortran"},
	{{".go"}, "Go"},
	{{".html", ".htm"},				"HTML"},
	{{".hs"},						"Haskell"},
	{{".json"},						"JSON"},
	{{".java"},						"Java"},
	{{".js"},						"JavaScript"},
	{{".jl"},						"Julia"},
	{{".kt", ".kts", ".ktm"},		"Kotlin"},
	{{".lex"},						"Lex"},
	{{".lua"},						"Lua"},
	{{".mk"},						"Make"},
	{{".md"},						"Markdown"},
	{{".m"},						"Obj-C"},
	{{".mm"},						"Obj-C++"},
	{{".pas", ".pp"},				"Pascal"},
	{{".py"},						"Python"},
	{{".rb", ".ru", ".ruby"},		"Ruby"},
	{{".rs"},						"Rust"},
	{{".sql"},						"SQL"},
	{{".scala"},					"Scala"},
	{{".sh", ".bash"},				"Shell"},
	{{".swift"},					"Swift"},
	{{".tex"},						"TeX"},
	{{".ts"},						"TypeScript"},
	{{".vb", ".vbs"},				"Visual B"},
	{{".xml"},						"XML"},
	{{".yml", ".yaml"},				"YAML"}
};

const FSExtension __fs_file_extensions_image = {
	{{".png", ".jpg", ".jpeg", ".ico", ".gif", ".bmp"}, "Image"}
};

const FSExtension __fs_file_extensions_video = {
	{{".mp4", ".mov", ".wmv", ".mpg"}, "Video"}
};

const FSExtension __fs_file_extensions_audio = {
	{{".mp3", ".wav", ".ogg", ".mp2",}, "Audio"}
};

const FSExtension __fs_file_extensions_binary = {
	{{".exe", ".dll", ".sys", ".bin", ".dat", ".iso", ".jar", ".reg"}, "Binary"}
};


const std::string __word_separator = "=+-*/()[]{}<>?;:,|&\\!#@$ ";

 BaseColorStructure* __clr_autocomplete_suggestion = new IdColorStructure(240);

BaseColorStructure* __clr_quoted = new IdColorStructure(106);
BaseColorStructure* __clr_escape_char = new IdColorStructure(209);

BaseColorStructure* __clr_identifier = new IdColorStructure(115);
BaseColorStructure* __clr_ex_identifier = new IdColorStructure(115, italic);
BaseColorStructure* __clr_ex_sys_identifier = new IdColorStructure(178, italic);

BaseColorStructure* __clr_flag = new IdColorStructure(157);

BaseColorStructure* __clr_command = new IdColorStructure(141);
BaseColorStructure* __clr_ex_command = new IdColorStructure(141, italic);

BaseColorStructure* __clr_ret_command = new IdColorStructure(162);
BaseColorStructure* __clr_ex_ret_command = new IdColorStructure(162, italic);
BaseColorStructure* __clr_sys_ret_command = new IdColorStructure(203);
BaseColorStructure* __clr_ex_sys_ret_command = new IdColorStructure(203, italic);

BaseColorStructure* __clr_numbers = new IdColorStructure(192);
BaseColorStructure* __clr_operators = new IdColorStructure(222);

BaseColorStructure* __clr_encloses_s1 = new IdColorStructure(210);
BaseColorStructure* __clr_encloses_s2 = new IdColorStructure(113);
BaseColorStructure* __clr_encloses_s3 = new IdColorStructure(117);
BaseColorStructure* __clr_encloses_s4 = new IdColorStructure(220);

BaseColorStructure* __clr_cursor = new IdColorStructure(75, underline);
BaseColorStructure* __clr_keyword = new IdColorStructure(170);
BaseColorStructure* __clr_boolean = new IdColorStructure(219);

BaseColorStructure* __clr_fs_file_type_regular = new ColorStructure(null);
BaseColorStructure* __clr_fs_file_type_symlink = new IdColorStructure(209);
BaseColorStructure* __clr_fs_file_type_dir = new IdColorStructure(120);
BaseColorStructure* __clr_fs_file_type_hidden = new IdColorStructure(168);
BaseColorStructure* __clr_fs_file_type_archive = new IdColorStructure(110);
BaseColorStructure* __clr_fs_file_type_temporary = new IdColorStructure(98);
BaseColorStructure* __clr_fs_file_type_other = new IdColorStructure(107);


BaseColorStructure* __clr_fs_filesize1 = new IdColorStructure(77);
BaseColorStructure* __clr_fs_filesize2 = new IdColorStructure(81);
BaseColorStructure* __clr_fs_filesize3 = new IdColorStructure(215);
BaseColorStructure* __clr_fs_filesize4 = new IdColorStructure(196);

BaseColorStructure* __clr_fs_file_extension_text = new IdColorStructure(216);
BaseColorStructure* __clr_fs_file_extension_image = new IdColorStructure(220);
BaseColorStructure* __clr_fs_file_extension_video = new IdColorStructure(183);
BaseColorStructure* __clr_fs_file_extension_audio = new IdColorStructure(42);
BaseColorStructure* __clr_fs_file_extension_binary = new IdColorStructure(242);
BaseColorStructure* __clr_fs_file_extension_other = new ColorStructure(null);

BaseColorStructure* __clr_help_param_name = new IdColorStructure(228);
BaseColorStructure* __clr_help_optional = new IdColorStructure(169);
BaseColorStructure* __clr_help_undefined_param_size = new IdColorStructure(208);

BaseColorStructure* __clr_type_literal = new IdColorStructure(113);
BaseColorStructure* __clr_type_number = new IdColorStructure(192);
BaseColorStructure* __clr_type_bool = new IdColorStructure(219);
BaseColorStructure* __clr_type_list = new IdColorStructure(38);
BaseColorStructure* __clr_type_object = new IdColorStructure(215);
BaseColorStructure* __clr_type_any = new IdColorStructure(198);