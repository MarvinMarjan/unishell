#pragma once

#include "defBase.h"

// size
START_COMMAND(LiteralRetCmdSize, ParamVec({ {nullptr, {Literal}} }), RetCommandBase, "size", CmdFunc::Literal)
LiteralValue* exec() override {
	return lit((double)asStr(args[0]).size());
}
END_COMMAND



// at
START_COMMAND(LiteralRetCmdAt, ParamVec({ {nullptr, {Literal}}, {nullptr, {Number}} }), RetCommandBase, "at", CmdFunc::Literal)
LiteralValue* exec() override
{
	const std::string src = asStr(args[0]);
	const int index = (int)asDbl(args[1]);

	checkIndex(index, src.size(), symbol);
	return lit(alg::string::charToStr(src.at(index)));
}
END_COMMAND

// sub
START_COMMAND(LiteralRetCmdSub, ParamVec({ {nullptr, {Literal}}, {nullptr, {Number}}, {nullptr, {Number}} }), RetCommandBase, "sub", CmdFunc::Literal)
LiteralValue* exec() override {
	const std::string src = asStr(args[0]);
	const int begin = (int)asDbl(args[1]);
	const int end = (int)asDbl(args[2]);

	checkIndex(begin, src.size(), symbol);
	checkIndex(end, src.size(), symbol);

	return lit(src.substr(begin, (size_t)end + 1 - begin));
}
END_COMMAND


// erase
START_COMMAND(LiteralRetCmdErase, ParamVec({ {nullptr, {Literal}}, {nullptr, {Number}}, {nullptr, {Number}} }), RetCommandBase, "erase", CmdFunc::Literal)
LiteralValue* exec() override {
	std::string* const src = &asStr(args[0]);
	const int begIndex = (int)asDbl(args[1]), endIndex = (int)asDbl(args[2]);
	const int current = 0;

	checkIndex(begIndex, src->size(), symbol);
	checkIndex(endIndex, src->size(), symbol);

	src->erase(src->begin() + begIndex, src->begin() + endIndex + 1);

	return args[0];
}
END_COMMAND



// split
START_COMMAND(LiteralRetCmdSplit, ParamVec({ {nullptr, {Literal}}, {lit(" "), {Literal}} }), RetCommandBase, "split", CmdFunc::Literal)
LiteralValue* exec() override {
	if (asStr(args[1]).size() > 1)
		THROW_RUNTIME_ERR("Single character Literal expected: " + qtd(asStr(args[1])));

	LiteralValue* list = lit(LitList());

	for (const std::string& item : alg::string::split(asStr(args[0]), asStr(args[1])[0]))
		asList(list).push_back(lit(item));

	return list;
}
END_COMMAND

// join
START_COMMAND(LiteralRetCmdJoin, ParamVec({ {nullptr, {List}}, { lit(" "), {Literal}} }), RetCommandBase, "join", CmdFunc::Literal)
LiteralValue* exec() override {
	if (!TypeUtil::isListOf(args[0], Literal))
		THROW_RUNTIME_ERR("Only Literal type List accepted: " + litToStr(args[0], true));

	return lit(alg::vector::join(alg::vector::map<LiteralValue*, std::string>(asList(args[0]), [](LiteralValue* val) {
		return asStr(val);
		}), asStr(args[1])));
}
END_COMMAND