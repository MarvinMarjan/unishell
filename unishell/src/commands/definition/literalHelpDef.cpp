#include "literal.h"

// size
START_HELP(LiteralRetCmdSize)
return { .name = LiteralRetCmdSize().symbol, .params = {{"Value", {Literal}}}, .description = "returns the size of ^0." };
END_HELP

// at
START_HELP(LiteralRetCmdAt)
return { .name = LiteralRetCmdAt().symbol, .params = {{"Value", {Literal}}, {"Where", {Number}}},
			.description = "returns the value inside ^0 at ^1." };
END_HELP

// erase
START_HELP(LiteralRetCmdErase)
return { .name = LiteralRetCmdErase().symbol, .params = {{"Source", {Literal}}, {"Begin", {Number}}, {"End", {Number}}},
			.description = "erases values int ^0 between ^1 and ^2 and returns ^0." };
END_HELP

// sub
START_HELP(LiteralRetCmdSub)
return { .name = LiteralRetCmdSub().symbol, .params = {{"Value", {Literal}}, {"Begin", {Number}}, {"End", {Number}}},
			.description = "returns a sub string between index ^1 and ^2." };
END_HELP

// split
START_HELP(LiteralRetCmdSplit)
return { .name = LiteralRetCmdSplit().symbol, .params = {{"Value", {Literal}}, {"Separator", {Literal}, true}},
			.description = "splits ^0 in every ^1 (single char)." };
END_HELP

// join
START_HELP(LiteralRetCmdJoin)
return { .name = LiteralRetCmdJoin().symbol, .params = {{"Source", {List}}, {"Separator", {Literal}, true}},
			.description = "joins every value in ^0 (Literal-only List) separating with ^1 and returns the result." };
END_HELP