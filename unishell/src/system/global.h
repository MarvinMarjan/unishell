#pragma once

#include "../utilities/stringUtil.h"
#include "../outstream/colorStructure.h"

#include "../parser/instream/token.h"

// global variables

// a map of keywords. left is the keyword name,
// right is the keywords token representation
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
	"null",
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

// --> global color variables
extern BaseColorStructure* __clr_quoted;
extern BaseColorStructure* __clr_identifier;
extern BaseColorStructure* __clr_command;
extern BaseColorStructure* __clr_numbers;
extern BaseColorStructure* __clr_operators;
extern BaseColorStructure* __clr_parens;
extern BaseColorStructure* __clr_cursor;
extern BaseColorStructure* __clr_keyword;
extern BaseColorStructure* __clr_boolean;
// <--