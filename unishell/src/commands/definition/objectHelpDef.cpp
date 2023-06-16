#include "object.h"

// size
START_HELP(ObjectRetCmdSize)
return { .name = ObjectRetCmdSize().symbol, .params = {{"Value", {lit::LitType::Object}}}, .description = "returns the size of ^0." };
END_HELP

// at
START_HELP(ObjectRetCmdAt)
return { .name = ObjectRetCmdAt().symbol, .params = {{"Value", {lit::LitType::Object}}, {"Where", {lit::LitType::Literal}}},
			.description = "returns the value inside ^0 at ^1." };
END_HELP

// insert
START_HELP(ObjectRetCmdInsert)
return { .name = ObjectRetCmdInsert().symbol, .params = {{"Source", {lit::LitType::Object}}, {"Name", {lit::LitType::Literal}}, {"Value", {lit::LitType::Any}}},
			.description = "inserts a pair of ^1 and ^2 into ^0 and returns ^0." };
END_HELP

// eraseAt
START_HELP(ObjectRetCmdEraseAt)
return { .name = ObjectRetCmdEraseAt().symbol, .params = {{"Source", {lit::LitType::Object}}, {"Where", {lit::LitType::Literal}}},
			.description = "erases item at ^1 location inside ^0 and returns ^0." };
END_HELP