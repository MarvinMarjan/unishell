#pragma once

#include "def.h"

#include "../../system/settings/json_fstream_handle.h"

// fromJson
START_COMMAND(JSONRetCmdFromJson, ParamVec({ {nullptr, {lit::LitType::Literal}} }), RetCommandBase, "fromJson", CmdFunc::JSON)
lit::LiteralValue* exec() override {
	const std::string strJson = asStr(args[0]);

	return JSONFstreamHandle::JSONValueToLiteralValue(json::parse(strJson));
}
END_COMMAND;

// toJson
START_COMMAND(JSONRetCmdToJson, ParamVec({ {nullptr, {lit::LitType::Any}} }), RetCommandBase, "toJson", CmdFunc::JSON)
lit::LiteralValue* exec() override {
	return lit::lit(JSONFstreamHandle::LiteralValueToJSONValue(args[0]).dump(2));
}
END_COMMAND;