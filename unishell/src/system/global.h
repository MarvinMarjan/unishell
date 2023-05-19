#pragma once

#include "../utilities/stringUtil.h"
#include "../outstream/colorStructure.h"

#include <map>

// global variables

const StringList __keywords = {
	"and",
	"or"
};

const StringList __boolean = {
	"true",
	"false"
};

// --> global color variables
extern ColorStructure __clr_quoted;
extern ColorStructure __clr_identifier;
extern ColorStructure __clr_command;
extern ColorStructure __clr_numbers;
extern ColorStructure __clr_operators;
extern ColorStructure __clr_parens;
extern ColorStructure __clr_cursor;
extern ColorStructure __clr_keyword;
extern ColorStructure __clr_boolean;
// <--