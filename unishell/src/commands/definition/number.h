#pragma once

#include "def.h"

#include "../../data/litvalue/checking.h"

#include <cmath>

// round
START_COMMAND(NumberRetCmdRound, ParamVec({ {nullptr, {lit::LitType::Number}} }), RetCommandBase, "round", CmdFunc::Number)
lit::LiteralValue* exec() override {
	return lit::lit(std::round(asDbl(args[0])));
}
END_COMMAND

// isDecimal
START_COMMAND(NumberRetCmdIsDecimal, ParamVec({ {nullptr, {lit::LitType::Number}} }), RetCommandBase, "isDecimal", CmdFunc::Number)
lit::LiteralValue* exec() override {
	return lit::lit(!lit::isIntNumber(asDbl(args[0])));
}
END_COMMAND