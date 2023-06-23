#include "option_format.h"

std::string formatSection(const Section& section, int& optionIndex) noexcept
{
	std::stringstream str;
	int space = 0;

	for (const Option& option : section.getAllOptions())
		if (option.name().size() > space)
			space = (int)option.name().size();
	
	for (const Option& option : section.getAllOptions()) {
		str << __clr_numbers->toString() << std::setw(5) << std::left << tostr(optionIndex) + '.' << endclr << formatOption(option, space) << "\n";
		optionIndex++;
	}

	return str.str();
}

std::string formatOption(const Option& option, int space) noexcept
{
	std::stringstream str;
	std::string strVal = litToStr(option.value_);

	if (space == -1)
		space = (int)option.name().size();

	if (option.valueRepresentsColor_) {
		const TokenList valTokens = InstreamScanner(litToStr(option.value_), IgnoreCommand).scanTokens();
		BaseColorStructure* color = ColorParser(valTokens).parse();

		strVal = clr(strVal, color->toString());
	}

	str << std::setw(space + 3) << std::left << option.name_ + ':' << strVal;

	return str.str();
}
