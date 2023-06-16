#pragma once

#include "defBase.h"

// at
START_COMMAND(ListRetCmdAt, ParamVec({ {nullptr, {lit::LitType::List}}, {nullptr, {lit::LitType::Number}} }), RetCommandBase, "at", CmdFunc::List)
lit::LiteralValue* exec() override
{
	const lit::LitList src = asList(args[0]);
	const int index = (int)asDbl(args[1]);

	checkIndex(index, src.size(), symbol);
	return src.at(index);
}
END_COMMAND



// size
START_COMMAND(ListRetCmdSize, ParamVec({ {nullptr, {lit::LitType::List}} }), RetCommandBase, "size", CmdFunc::List)
lit::LiteralValue* exec() override {
	return lit::lit((double)asList(args[0]).size());
}
END_COMMAND



// append
START_COMMAND(ListRetCmdAppend, ParamVec({ {nullptr, {lit::LitType::List}}, {nullptr} }), RetCommandBase, "append", CmdFunc::List)
lit::LiteralValue* exec() override {
	if (args[0]->type() == lit::LitType::List)
		for (size_t i = 1; i < args.size(); i++)
			asList(args[0]).push_back(args[i]);

	return args[0];
}
END_COMMAND

// erase
START_COMMAND(ListRetCmdErase, ParamVec({ {nullptr, {lit::LitType::List}}, {nullptr, {lit::LitType::Number}}, {nullptr, {lit::LitType::Number}} }), RetCommandBase, "erase", CmdFunc::List)
lit::LiteralValue* exec() override {
	lit::LitList* const src = &asList(args[0]);
	const int begIndex = (int)asDbl(args[1]), endIndex = (int)asDbl(args[2]);

	checkIndex(begIndex, src->size(), symbol);
	checkIndex(endIndex, src->size(), symbol);

	src->erase(src->begin() + begIndex, src->begin() + endIndex + 1);

	return args[0];
}
END_COMMAND

// eraseAt
START_COMMAND(ListRetCmdEraseAt, ParamVec({ {nullptr, {lit::LitType::List}}, {nullptr, {lit::LitType::Number}} }), RetCommandBase, "eraseAt", CmdFunc::List)
lit::LiteralValue* exec() override {
	lit::LitList* const src = &asList(args[0]);
	const int index = (int)asDbl(args[1]);

	checkIndex(index, src->size(), symbol);

	src->erase(src->begin() + index);

	return args[0];
}
END_COMMAND