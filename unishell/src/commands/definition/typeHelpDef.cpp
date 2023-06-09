#include "type.h"

// type
START_HELP(TypeRetCmdType)
return { .name = TypeRetCmdType().symbol, .params = {{"Value", {Any}}}, .description = "returns the type of ^0." };
END_HELP

// literal
START_HELP(TypeRetCmdLiteral)
return { .name = TypeRetCmdLiteral().symbol, .params = {{"Value", {Literal, Number, Bool}}}, .description = "converts ^0 into a Literal type." };
END_HELP

// number
START_HELP(TypeRetCmdNumber)
return { .name = TypeRetCmdNumber().symbol, .params = {{"Value", {Literal}}}, .description = "try to convert ^0 into a Number type." };
END_HELP

// bool
START_HELP(TypeRetCmdBool)
return { .name = TypeRetCmdBool().symbol, .params = {{"Value", {Literal}}}, .description = "converts ^0 into a Bool type." };
END_HELP