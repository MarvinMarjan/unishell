#pragma once

#include <string>

enum SystemExceptionType
{

};

class SystemException
{
public:
	SystemException(const std::string& msg, const std::string& arg = "") : msg(msg), arg(arg)
	{}

	SystemException(SystemExceptionType type)
	{
		switch (type)
		{
		default:
			ignoreCurrentIndexChange("");
		}
	}

	inline std::string toString() const noexcept {
		return msg + ((arg.empty()) ? "" : ": " + arg);
	}

private:
	inline void ignoreCurrentIndexChange(const std::string& msg, const std::string& arg = "") noexcept {
		this->msg = msg;
		this->arg = arg;
	}

	std::string msg;
	std::string arg;
};