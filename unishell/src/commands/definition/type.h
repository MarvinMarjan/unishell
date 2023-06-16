#pragma once

#include "defBase.h"

// type
START_COMMAND(TypeRetCmdType, { nullptr }, RetCommandBase, "type", CmdFunc::Type)
lit::LiteralValue* exec() override {
	return lit::lit(lit::getTypeAsString(lit::LiteralValue::typeof(args[0])));
}
END_COMMAND

// literal
START_COMMAND(TypeRetCmdLiteral, ParamVec({ {nullptr, {lit::LitType::Literal, lit::LitType::Number, lit::LitType::Bool}} }), RetCommandBase, "literal", CmdFunc::Type)
lit::LiteralValue* exec() override {
	return lit::lit(litToStr(args[0]));
}
END_COMMAND

// number
START_COMMAND(TypeRetCmdNumber, ParamVec({ {nullptr, {lit::LitType::Literal}} }), RetCommandBase, "number", CmdFunc::Type)
lit::LiteralValue* exec() override {
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

	return lit::lit(res);
}
END_COMMAND

// bool
START_COMMAND(TypeRetCmdBool, ParamVec({ {nullptr, {lit::LitType::Literal}} }), RetCommandBase, "bool", CmdFunc::Type)
lit::LiteralValue* exec() override {
	return lit::lit(lit::stringToBool(asStr(args[0])));
}
END_COMMAND
