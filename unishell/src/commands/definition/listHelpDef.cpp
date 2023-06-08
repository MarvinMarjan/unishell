#include "list.h"

// size
START_HELP(ListRetCmdSize)
return { .name = ListRetCmdSize::symbol, .params = {{"Value", {List}}}, .description = "returns the size of ^0." };
END_HELP

// at
START_HELP(ListRetCmdAt)
return { .name = ListRetCmdAt::symbol, .params = {{"Value", {List}}, {"Where", {Number}}},
			.description = "returns the value inside ^0 at ^1." };
END_HELP

// append
START_HELP(ListRetCmdAppend)
return { .name = ListRetCmdAppend::symbol, .params = {{"Source", {List}}, {"Value", {Any}}},
			.description = "appends ^1 into ^0 and returns ^0." };
END_HELP

// erase
START_HELP(ListRetCmdErase)
return { .name = ListRetCmdErase::symbol, .params = {{"Source", {List}}, {"Begin", {Number}}, {"End", {Number}}},
			.description = "erases values int ^0 between ^1 and ^2 and returns ^0." };
END_HELP

// eraseAt
START_HELP(ListRetCmdEraseAt)
return { .name = ListRetCmdEraseAt::symbol, .params = {{"Source", {List}}, {"Where", {Number}}},
			.description = "erases item at ^1 location inside ^0 and returns ^0." };
END_HELP
