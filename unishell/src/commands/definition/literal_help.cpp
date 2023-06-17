#include "literal.h"

// size
START_HELP(LiteralRetCmdSize)
return { .name = LiteralRetCmdSize().symbol, .params = {{"Value", {lit::LitType::Literal}}}, .description = "returns the size of ^0." };
END_HELP

// at
START_HELP(LiteralRetCmdAt)
return { .name = LiteralRetCmdAt().symbol, .params = {{"Value", {lit::LitType::Literal}}, {"Where", {lit::LitType::Number}}},
			.description = "returns the value inside ^0 at ^1." };
END_HELP

// erase
START_HELP(LiteralRetCmdErase)
return { .name = LiteralRetCmdErase().symbol, .params = {{"Source", {lit::LitType::Literal}}, {"Begin", {lit::LitType::Number}}, {"End", {lit::LitType::Number}}},
			.description = "erases values int ^0 between ^1 and ^2 and returns ^0." };
END_HELP

// sub
START_HELP(LiteralRetCmdSub)
return { .name = LiteralRetCmdSub().symbol, .params = {{"Value", {lit::LitType::Literal}}, {"Begin", {lit::LitType::Number}}, {"End", {lit::LitType::Number}}},
			.description = "returns a sub string between index ^1 and ^2." };
END_HELP

// split
START_HELP(LiteralRetCmdSplit)
return { .name = LiteralRetCmdSplit().symbol, .params = {{"Value", {lit::LitType::Literal}}, {"Separator", {lit::LitType::Literal}, true}},
			.description = "splits ^0 in every ^1 (single char)." };
END_HELP

// join
START_HELP(LiteralRetCmdJoin)
return { .name = LiteralRetCmdJoin().symbol, .params = {{"Source", {lit::LitType::List}}, {"Separator", {lit::LitType::Literal}, true}},
			.description = "joins every value in ^0 (Literal-only List) separating with ^1 and returns the result." };
END_HELP