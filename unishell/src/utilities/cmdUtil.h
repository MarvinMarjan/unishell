#pragma once

#include "../commands/cmdsDef.h"

class CmdUtil
{
public:
	static inline ArgList getArgs(TokenList input, bool encapsulate = true, bool firstIsCommand = true, bool* hasExplicitList = nullptr) {
		size_t index = (firstIsCommand) ? 1 : 0;

		if (input.size() <= index) return ArgList(); // has no args

		if (encapsulate) {
			size_t i = index;
			for (i; i < input.size(); i++) {}
			return ArgList(TokenList(input.begin() + index, input.begin() + i));
		}

		else if (input[index].getType() == LIST) {
			if (hasExplicitList != nullptr)
				*hasExplicitList = true;

			return ArgList(input[index]);
		}

		return ArgList();
	}

	static inline CommandBase* getCommand(const std::string& cmdName, ArgList args) {
		CHECK_CMD(CmdPrint);
		CHECK_CMD(CmdClear);
		CHECK_CMD(CmdCd);
		CHECK_CMD(CmdLs);

		CHECK_CMD(CmdVar);
		CHECK_CMD(CmdDel);
		
		CHECK_CMD(CmdExit);

		return nullptr;
	}
	static inline RetCommandBase* getRetCommand(const std::string& cmdName, ArgList args) {
		CHECK_CMD(RetCmdInput);
		
		CHECK_CMD(RetCmdType);
		CHECK_CMD(RetCmdSize);

		CHECK_CMD(RetCmdAt);
		CHECK_CMD(RetCmdSub);
		CHECK_CMD(RetCmdSplit);
		CHECK_CMD(RetCmdJoin);

		CHECK_CMD(RetCmdLiteral);
		CHECK_CMD(RetCmdNumber);
		CHECK_CMD(RetCmdBool);

		return nullptr;
	}

};
