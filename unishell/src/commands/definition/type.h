#pragma once

#include "defBase.h"

// type
START_COMMAND(TypeRetCmdType, { nullptr }, RetCommandBase, "type", CmdFunc::Type)
LiteralValue* exec() override {
	return litStr(TypeUtil::getTypeAsString(getValueType(args[0])));
}
END_COMMAND

// literal
START_COMMAND(TypeRetCmdLiteral, ParamVec({ {nullptr, {Literal, Number, Bool}} }), RetCommandBase, "literal", CmdFunc::Type)
LiteralValue* exec() override {
	return litStr(litToStr(args[0]));
}
END_COMMAND

// number
START_COMMAND(TypeRetCmdNumber, ParamVec({ {nullptr, {Literal}} }), RetCommandBase, "number", CmdFunc::Type)
LiteralValue* exec() override {
	double res;
	
	try {
		res = std::stod(litToStr(args[0]));
	}
	catch (const std::invalid_argument&) {
		THROW_RUNTIME_ERR("Unable to convert: " + qtd(asStr(args[0])));
	}
	catch (const std::out_of_range&) {
		THROW_RUNTIME_ERR("Value too large: " + qtd(asStr(args[0])));
	}

	return litNum(res);
}
END_COMMAND

// bool
START_COMMAND(TypeRetCmdBool, ParamVec({ {nullptr, {Literal}} }), RetCommandBase, "bool", CmdFunc::Type)
LiteralValue* exec() override {
	return litBool(TypeUtil::stringToBool(asStr(args[0])));
}
END_COMMAND
