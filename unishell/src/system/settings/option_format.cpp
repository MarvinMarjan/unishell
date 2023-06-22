#include "option_format.h"

std::string formatOption(const Option& option) noexcept
{
	std::stringstream str;
	std::string strVal = litToStr(option.value_);

	if (option.valueRepresentsColor_) {
		const TokenList valTokens = InstreamScanner(litToStr(option.value_), IgnoreCommand).scanTokens();
		BaseColorStructure* color = ColorParser(valTokens).parse();

		strVal = clr(strVal, color->toString());
	}

	str << option.name_ << ":  " << strVal;

	return str.str();
}