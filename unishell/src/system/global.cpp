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
	"var",
	"del",
	"exit"
};

const StringList __sys_ret_commands = {
	"type",
	"size",
	"at"
};

const std::string __word_separator = "=+-*/()[]{}<>?;:,|\\! ";

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
BaseColorStructure* __clr_encloses = new IdColorStructure(210);
BaseColorStructure* __clr_cursor = new IdColorStructure(75, underline);
BaseColorStructure* __clr_keyword = new IdColorStructure(170);
BaseColorStructure* __clr_boolean = new IdColorStructure(219);