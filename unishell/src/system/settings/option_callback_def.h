#pragma once

#include "../../data/litvalue/type.h"
#include "../../color/structure/color_structure.h"
#include "../../color/parser/color_parser.h"
#include "../../instream/scanner/instream_scanner.h"
#include "../memory/memfree.h"


#define onValueChange_BaseColorStructure(clr_pointer) \
	[] (lit::LiteralValue* value) { \
		const TokenList loc_tokens = InstreamScanner(asStr(value), IgnoreCommand).scanTokens(); \
		\
		if (clr_pointer) \
			delete clr_pointer; \
		\
		clr_pointer = ColorParser(loc_tokens, true).parse(); \
		\
		freeTokenListMemory(loc_tokens); \
	}



#define onValueChange_boolean(boolean_val) \
	[] (lit::LiteralValue* value) { \
		boolean_val = asBool(value); \
	}

