#pragma once

#include "def.h"

#include "../../data/litvalue/obj_predef.h"

// match
START_COMMAND(RegexRetCmdMatch, ParamVec({ {nullptr, {lit::LitType::Literal}}, {nullptr, {lit::LitType::Literal}} }), RetCommandBase, "match", CmdFunc::Regex)
lit::LiteralValue* exec() override {
	lit::LiteralValue* list = lit::lit(lit::LitList());

	if (asStr(args[1]).empty())
		THROW_RUNTIME_ERR("Empty regex pattern: " + qtd(asStr(args[1])));

	std::string src = asStr(args[0]);
	const std::regex pattern(asStr(args[1]));

	std::smatch matches;
	std::string::const_iterator searchStart(src.cbegin());
	while (std::regex_search(searchStart, src.cend(), matches, pattern)) {
		asList(list).push_back(lit::newRegexResultObj(matches));
		searchStart = matches.suffix().first;
	}

	return list;
}
END_COMMAND

// replace
START_COMMAND(RegexRetCmdReplace, ParamVec({ {nullptr, {lit::LitType::Literal}}, {nullptr, {lit::LitType::Literal}}, {nullptr, {lit::LitType::Literal}} }), RetCommandBase, "replace", CmdFunc::Regex)
lit::LiteralValue* exec() override {
	std::string src = asStr(args[0]);
	std::string repStr = asStr(args[2]);

	if (asStr(args[1]).empty())
		THROW_RUNTIME_ERR("Empty regex pattern: " + qtd(asStr(args[1])));

	std::regex pattern(asStr(args[1]));

	src = std::regex_replace(src, pattern, repStr);

	return lit::lit(src);
}
END_COMMAND