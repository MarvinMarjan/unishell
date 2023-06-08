#pragma once

#include "defBase.h"

// at
START_COMMAND(ObjectRetCmdAt, ParamVec({ {nullptr, {Object}}, {nullptr, {Literal} } }), RetCommandBase, "at", CmdFunc::Object)
LiteralValue* exec() override
{
	LiteralValueObj src = asObj(args[0]);
	std::string key = asStr(args[1]);

	checkIndex(src, key, symbol);
	return src.at(key);
}
END_COMMAND

// size
START_COMMAND(ObjectRetCmdSize, ParamVec({ {nullptr, {Object}} }), RetCommandBase, "size", CmdFunc::Object)
LiteralValue* exec() override {
 return litNum((double)asObj(args[0]).size());
}
END_COMMAND

// insert
START_COMMAND(ObjectRetCmdInsert, ParamVec({ {nullptr, {Object}}, {nullptr, {Literal}}, {nullptr} }), RetCommandBase, "insert", CmdFunc::Object)
LiteralValue* exec() override {
	asObj(args[0]).insert({ asStr(args[1]), args[2] });

	return args[0];
}
END_COMMAND;

// eraseAt
START_COMMAND(ObjectRetCmdEraseAt, ParamVec({ {nullptr, {Object}}, {nullptr, {Literal}} }), RetCommandBase, "eraseAt", CmdFunc::Object)
LiteralValue* exec() override {
	LiteralValueObj* src = &asObj(args[0]);
	LiteralValue* at = args[1];

	std::string key = asStr(at);

	checkIndex(*src, key, symbol);

	src->erase(key);

	return args[0];
}
END_COMMAND