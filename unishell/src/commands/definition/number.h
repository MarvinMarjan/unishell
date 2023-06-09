#pragma once

#include "defBase.h"

// round
START_COMMAND(NumberRetCmdRound, ParamVec({ {nullptr, {Number}} }), RetCommandBase, "round", CmdFunc::Number)
LiteralValue* exec() override {
	return lit(std::round(asDbl(args[0])));
}
END_COMMAND

// isDecimal
START_COMMAND(NumberRetCmdIsDecimal, ParamVec({ {nullptr, {Number}} }), RetCommandBase, "isDecimal", CmdFunc::Number)
LiteralValue* exec() override {
	return lit(!TypeUtil::isInteger(asDbl(args[0])));
}
END_COMMAND