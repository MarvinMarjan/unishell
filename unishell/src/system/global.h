#pragma once

#include "../utilities/stringUtil.h"
#include "../outstream/colorStructure.h"

#include "../parser/instream/token.h"

// global variables

extern const StringList __keywords;
extern const StringList __boolean;
extern const StringList __colormode;
extern const StringList __color;
extern const StringList __color_formats;
extern const StringList __commands;

extern const std::string __word_separator;

// --> global color variables
extern BaseColorStructure* __clr_quoted;

extern BaseColorStructure* __clr_identifier;
extern BaseColorStructure* __clr_ex_identifier;
extern BaseColorStructure* __clr_ex_sys_identifier;

extern BaseColorStructure* __clr_command;
extern BaseColorStructure* __clr_ex_command;

extern BaseColorStructure* __clr_numbers;
extern BaseColorStructure* __clr_operators;
extern BaseColorStructure* __clr_encloses;
extern BaseColorStructure* __clr_cursor;
extern BaseColorStructure* __clr_keyword;
extern BaseColorStructure* __clr_boolean;
// <--