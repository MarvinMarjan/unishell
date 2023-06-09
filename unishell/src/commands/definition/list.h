#pragma once

#include "defBase.h"

// at
START_COMMAND(ListRetCmdAt, ParamVec({ {nullptr, {List}}, {nullptr, {Number}} }), RetCommandBase, "at", CmdFunc::List)
LiteralValue* exec() override
{
	LiteralValueList src = asList(args[0]);
	int index = (int)asDbl(args[1]);

	checkIndex(index, src.size(), symbol);
	return src.at(index);
}
END_COMMAND



// size
START_COMMAND(ListRetCmdSize, ParamVec({ {nullptr, {List}} }), RetCommandBase, "size", CmdFunc::List)
LiteralValue* exec() override {
	return litNum((double)asList(args[0]).size());
}
END_COMMAND



// append
START_COMMAND(ListRetCmdAppend, ParamVec({ {nullptr, {List}}, {nullptr} }), RetCommandBase, "append", CmdFunc::List)
LiteralValue* exec() override {
	if (args[0]->type() == List)
		for (size_t i = 1; i < args.size(); i++)
			asList(args[0]).push_back(args[i]);

	return args[0];
}
END_COMMAND

// erase
START_COMMAND(ListRetCmdErase, ParamVec({ {nullptr, {List}}, {nullptr, {Number}}, {nullptr, {Number}} }), RetCommandBase, "erase", CmdFunc::List)
LiteralValue* exec() override {
	LiteralValueList* src = &asList(args[0]);
	int begIndex = (int)asDbl(args[1]), endIndex = (int)asDbl(args[2]);
	int current = 0;

	checkIndex(begIndex, src->size(), symbol);
	checkIndex(endIndex, src->size(), symbol);

	src->erase(src->begin() + begIndex, src->begin() + endIndex + 1);

	return args[0];
}
END_COMMAND

// eraseAt
START_COMMAND(ListRetCmdEraseAt, ParamVec({ {nullptr, {List}}, {nullptr, {Number}} }), RetCommandBase, "eraseAt", CmdFunc::List)
LiteralValue* exec() override {
	LiteralValueList* src = &asList(args[0]);
	int index = (int)asDbl(args[1]);

	checkIndex(index, src->size(), symbol);

	src->erase(src->begin() + index);

	return args[0];
}
END_COMMAND