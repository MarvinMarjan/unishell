#include "number.h"

// round
START_HELP(NumberRetCmdRound)
return { .name = NumberRetCmdRound().symbol, .params = {{"Value", {Number}}}, .description = "rounds ^0." };
END_HELP

// isDecimal
START_HELP(NumberRetCmdIsDecimal)
return { .name = NumberRetCmdIsDecimal().symbol, .params = {{"Value", {Number}}}, .description = "returns true if ^0 has decimal numbers." };
END_HELP