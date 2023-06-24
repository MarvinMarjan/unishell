#include "option.h"

#include "../../instream/scanner/instream_scanner.h"
#include "../../color/parser/color_parser.h"


bool Option::valueIsValid(lit::LiteralValue* value) {
	if (alg::vector::exists(types_, value->type()) || alg::vector::exists(types_, lit::LitType::Any))
	{
		if (value->type() == lit::LitType::Literal && valueRepresentsColor_)
			if (!ColorParser(InstreamScanner(asStr(value), IgnoreCommand).scanTokens(), true).parse())
				return false;

		return true;
	}

	return false;
}