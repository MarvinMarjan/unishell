#pragma once

#include "../global/typedecl.h"

#include "../exception/system_exception.h"

struct BootSettings
{
	std::string sourceFile;
};

struct AppFlag
{
	std::string flagName;
	int argIndex;
};

class Boot
{
public:
	Boot(char** argv, const int argc) {
		for (size_t i = 0; i < argc; i++)
			args_.push_back(std::string(argv[i]));
	}

	StringList args() const noexcept {
		return args_;
	}

	std::vector<AppFlag> flags() const noexcept {
		std::vector<AppFlag> flags;

		for (size_t i = 0; i < args_.size(); i++)
			if (args_[i][0] == '-')
				flags.push_back(AppFlag { .flagName = args_[i], .argIndex = (int)i });

		return flags;
	}

	BootSettings getBootSettings(std::vector<AppFlag> flags) {
		BootSettings sett;

		for (const AppFlag& flag : flags) {
			checkFlag(flag, sett.sourceFile, "-f");
		}

		return sett;
	}

private:
	void checkFlag(const AppFlag& flag, std::string& strSett, const std::string& expFlagName, bool requiresArg = true) {
		if (flag.flagName == expFlagName && (!requiresArg || (size_t)flag.argIndex + 1 < args_.size()))
			strSett = args_[(size_t)flag.argIndex + 1];

		else if (requiresArg && (size_t)flag.argIndex + 1 >= args_.size())
			throw new BootingErr(std::string("Flag ") + qtd(expFlagName) + " requires argument");
	}


	StringList args_;
};