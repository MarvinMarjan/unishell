#pragma once

#include "../../data/litvalue/type.h"
#include "../../color/structure/color_structure.h"
#include "../../color/parser/color_parser.h"
#include "../../instream/scanner/instream_scanner.h"


#define onValueChange_BaseColorStructure(clr_pointer) \
	[] (lit::LiteralValue* value) { \
		clr_pointer = ColorParser(InstreamScanner(asStr(value), IgnoreCommand).scanTokens(), true).parse(); \
	} \

