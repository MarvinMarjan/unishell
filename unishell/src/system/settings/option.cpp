#include "option.h"

#include "../../instream/scanner/instream_scanner.h"
#include "../../color/parser/color_parser.h"

#include "../../system/memory/memfree.h"

bool Option::valueIsValid(lit::LiteralValue* value) {
	if (alg::vector::exists(types_, value->type()) || alg::vector::exists(types_, lit::LitType::Any))
	{
		if (value->type() == lit::LitType::Literal && valueRepresentsColor_) {
			const TokenList tokens = InstreamScanner(asStr(value), IgnoreCommand).scanTokens();
			BaseColorStructure* color = ColorParser(tokens, true).parse();

			freeTokenListMemory(tokens);

			if (!color)
				return false;

			delete color;
		}

		return true;
	}

	return false;
}