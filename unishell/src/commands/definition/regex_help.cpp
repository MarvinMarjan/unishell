#include "regex.h"

// match
START_HELP(RegexRetCmdMatch)
return { .name = RegexRetCmdMatch().symbol, .params = {{"Source", {lit::LitType::Literal}}, {"Regex", {lit::LitType::Literal}}},
			.description = "applies the ^1 regular expression to ^0 and returns a List\n"
						   "\tcontaining each occurrence of the pattern in ^0." };
END_HELP

// replace
START_HELP(RegexRetCmdReplace)
return { .name = RegexRetCmdReplace().symbol, .params = {{"Source", {lit::LitType::Literal}}, {"Regex", {lit::LitType::Literal}}, {"Replacement", {lit::LitType::Literal}}},
			.description = "applies the ^1 regular expression to ^0 and replaces every occurrence\n"
						   "\tby ^2." };
END_HELP