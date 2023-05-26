#include "global.h"

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

	"var",
	"del",
	
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

	"literal",
	"number",
	"bool"
};

const std::string __word_separator = "=+-*/()[]{}<>?;:,|&\\!#@$ ";

BaseColorStructure* __clr_quoted = new IdColorStructure(106);

BaseColorStructure* __clr_identifier = new IdColorStructure(115);
BaseColorStructure* __clr_ex_identifier = new IdColorStructure(115, italic);
BaseColorStructure* __clr_ex_sys_identifier = new IdColorStructure(178, italic);

BaseColorStructure* __clr_command = new IdColorStructure(141);
BaseColorStructure* __clr_ex_command = new IdColorStructure(141, italic);

BaseColorStructure* __clr_ret_command = new IdColorStructure(162);
BaseColorStructure* __clr_ex_ret_command = new IdColorStructure(162, italic);
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