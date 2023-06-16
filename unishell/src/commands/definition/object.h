#pragma once

#include "defBase.h"

// at
START_COMMAND(ObjectRetCmdAt, ParamVec({ {nullptr, {lit::LitType::Object}}, {nullptr, {lit::LitType::Literal} } }), RetCommandBase, "at", CmdFunc::Object)
lit::LiteralValue* exec() override
{
	const lit::LitObject src = asObj(args[0]);
	const std::string key = asStr(args[1]);

	checkIndex(src, key, symbol);
	return src.at(key);
}
END_COMMAND

// size
START_COMMAND(ObjectRetCmdSize, ParamVec({ {nullptr, {lit::LitType::Object}} }), RetCommandBase, "size", CmdFunc::Object)
lit::LiteralValue* exec() override {
	return lit::lit((double)asObj(args[0]).size());
}
END_COMMAND

// insert
START_COMMAND(ObjectRetCmdInsert, ParamVec({ {nullptr, {lit::LitType::Object}}, {nullptr, {lit::LitType::Literal}}, {nullptr} }), RetCommandBase, "insert", CmdFunc::Object)
lit::LiteralValue* exec() override {
	asObj(args[0]).insert({ asStr(args[1]), args[2] });

	return args[0];
}
END_COMMAND;

// eraseAt
START_COMMAND(ObjectRetCmdEraseAt, ParamVec({ {nullptr, {lit::LitType::Object}}, {nullptr, {lit::LitType::Literal}} }), RetCommandBase, "eraseAt", CmdFunc::Object)
lit::LiteralValue* exec() override {
	lit::LitObject* src = &asObj(args[0]);
	lit::LiteralValue* at = args[1];

	const std::string key = asStr(at);

	checkIndex(*src, key, symbol);

	src->erase(key);

	return args[0];
}
END_COMMAND