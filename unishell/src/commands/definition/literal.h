#pragma once

#include "defBase.h"

// size
START_COMMAND(LiteralRetCmdSize, ParamVec({ {nullptr, {Literal}} }), RetCommandBase, "size", CmdFunc::Literal)
LiteralValue* exec() override {
	return litNum((double)asStr(args[0]).size());
}
END_COMMAND



// at
START_COMMAND(LiteralRetCmdAt, ParamVec({ {nullptr, {Literal}}, {nullptr, {Number}} }), RetCommandBase, "at", CmdFunc::Literal)
LiteralValue* exec() override
{
	std::string src = asStr(args[0]);
	int index = (int)asDbl(args[1]);

	checkIndex(index, src.size(), symbol);
	return litStr(StringUtil::charToStr(src.at(index)));
}
END_COMMAND

// sub
START_COMMAND(LiteralRetCmdSub, ParamVec({ {nullptr, {Literal}}, {nullptr, {Number}}, {nullptr, {Number}} }), RetCommandBase, "sub", CmdFunc::Literal)
LiteralValue* exec() override {
	std::string src = asStr(args[0]);
	int begin = (int)asDbl(args[1]);
	int end = (int)asDbl(args[2]);

	checkIndex(begin, src.size(), symbol);
	checkIndex(end, src.size(), symbol);

	return litStr(src.substr(begin, (size_t)end + 1 - begin));
}
END_COMMAND


// erase
START_COMMAND(LiteralRetCmdErase, ParamVec({ {nullptr, {Literal}}, {nullptr, {Number}}, {nullptr, {Number}} }), RetCommandBase, "erase", CmdFunc::Literal)
LiteralValue* exec() override {
	std::string* src = &asStr(args[0]);
	int begIndex = (int)asDbl(args[1]), endIndex = (int)asDbl(args[2]);
	int current = 0;

	checkIndex(begIndex, src->size(), symbol);
	checkIndex(endIndex, src->size(), symbol);

	src->erase(src->begin() + begIndex, src->begin() + endIndex + 1);

	return args[0];
}
END_COMMAND



// split
START_COMMAND(LiteralRetCmdSplit, ParamVec({ {nullptr, {Literal}}, {litStr(" "), {Literal}} }), RetCommandBase, "split", CmdFunc::Literal)
LiteralValue* exec() override {
	if (asStr(args[1]).size() > 1)
		THROW_RUNTIME_ERR("Single character Literal expected: " + qtd(asStr(args[1])));

	LiteralValue* list = litList({});

	for (const std::string& item : StringUtil::split(asStr(args[0]), asStr(args[1])[0]))
		asList(list).push_back(litStr(item));

	return list;
}
END_COMMAND

// join
START_COMMAND(LiteralRetCmdJoin, ParamVec({ {nullptr, {List}}, { litStr(" "), {Literal}} }), RetCommandBase, "join", CmdFunc::Literal)
LiteralValue* exec() override {
	if (!TypeUtil::isListOf(args[0], Literal))
		THROW_RUNTIME_ERR("Only Literal type List accepted: " + litToStr(args[0], true));

	return litStr(VectorUtil::join(VectorUtil::map<LiteralValue*, std::string>(asList(args[0]), [](LiteralValue* val) {
		return asStr(val);
		}), asStr(args[1])));
}
END_COMMAND