#pragma once

#include "defBase.h"
#include "../../data/litvalue/checking.h"

// size
START_COMMAND(LiteralRetCmdSize, ParamVec({ {nullptr, {lit::LitType::Literal}} }), RetCommandBase, "size", CmdFunc::Literal)
lit::LiteralValue* exec() override {
	return lit::lit((double)asStr(args[0]).size());
}
END_COMMAND



// at
START_COMMAND(LiteralRetCmdAt, ParamVec({ {nullptr, {lit::LitType::Literal}}, {nullptr, {lit::LitType::Number}} }), RetCommandBase, "at", CmdFunc::Literal)
lit::LiteralValue* exec() override
{
	const std::string src = asStr(args[0]);
	const int index = (int)asDbl(args[1]);

	checkIndex(index, src.size(), symbol);
	return lit::lit(alg::string::charToStr(src.at(index)));
}
END_COMMAND

// sub
START_COMMAND(LiteralRetCmdSub, ParamVec({ {nullptr, {lit::LitType::Literal}}, {nullptr, {lit::LitType::Number}}, {nullptr, {lit::LitType::Number}} }), RetCommandBase, "sub", CmdFunc::Literal)
lit::LiteralValue* exec() override {
	const std::string src = asStr(args[0]);
	const int begin = (int)asDbl(args[1]);
	const int end = (int)asDbl(args[2]);

	checkIndex(begin, src.size(), symbol);
	checkIndex(end, src.size(), symbol);

	return lit::lit(src.substr(begin, (size_t)end + 1 - begin));
}
END_COMMAND


// erase
START_COMMAND(LiteralRetCmdErase, ParamVec({ {nullptr, {lit::LitType::Literal}}, {nullptr, {lit::LitType::Number}}, {nullptr, {lit::LitType::Number}} }), RetCommandBase, "erase", CmdFunc::Literal)
lit::LiteralValue* exec() override {
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
START_COMMAND(LiteralRetCmdSplit, ParamVec({ {nullptr, {lit::LitType::Literal}}, {lit::lit(" "), {lit::LitType::Literal}} }), RetCommandBase, "split", CmdFunc::Literal)
lit::LiteralValue* exec() override {
	if (asStr(args[1]).size() > 1)
		THROW_RUNTIME_ERR("Single character Literal expected: " + qtd(asStr(args[1])));

	lit::LiteralValue* list = lit::lit(lit::LitList());

	for (const std::string& item : alg::string::split(asStr(args[0]), asStr(args[1])[0]))
		asList(list).push_back(lit::lit(item));

	return list;
}
END_COMMAND

// join
START_COMMAND(LiteralRetCmdJoin, ParamVec({ {nullptr, {lit::LitType::List}}, { lit::lit(" "), {lit::LitType::Literal}} }), RetCommandBase, "join", CmdFunc::Literal)
lit::LiteralValue* exec() override {
	if (!lit::isListOf(args[0], lit::LitType::Literal))
		THROW_RUNTIME_ERR("Only Literal type List accepted: " + litToStr(args[0], true));

	return lit::lit(alg::vector::join(alg::vector::map<lit::LiteralValue*, std::string>(asList(args[0]), [](lit::LiteralValue* val) {
		return asStr(val);
		}), asStr(args[1])));
}
END_COMMAND