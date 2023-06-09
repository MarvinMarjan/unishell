#include "object.h"

// size
START_HELP(ObjectRetCmdSize)
return { .name = ObjectRetCmdSize().symbol, .params = {{"Value", {Object}}}, .description = "returns the size of ^0." };
END_HELP

// at
START_HELP(ObjectRetCmdAt)
return { .name = ObjectRetCmdAt().symbol, .params = {{"Value", {Object}}, {"Where", {Literal}}},
			.description = "returns the value inside ^0 at ^1." };
END_HELP

// insert
START_HELP(ObjectRetCmdInsert)
return { .name = ObjectRetCmdInsert().symbol, .params = {{"Source", {Object}}, {"Name", {Literal}}, {"Value", {Any}}},
			.description = "inserts a pair of ^1 and ^2 into ^0 and returns ^0." };
END_HELP

// eraseAt
START_HELP(ObjectRetCmdEraseAt)
return { .name = ObjectRetCmdEraseAt().symbol, .params = {{"Source", {Object}}, {"Where", {Literal}}},
			.description = "erases item at ^1 location inside ^0 and returns ^0." };
END_HELP