#pragma once

#include "../utilities/stringUtil.h"
#include "../outstream/outputColor.h"

class ExceptionRef
{
public:
	ExceptionRef();

	ExceptionRef(const std::string& src, const int index = -1);
	ExceptionRef(const std::string& src, const size_t index);

	// return a string containing error location information
	std::string getString() const;

private:
	std::string src;
	int index;
};
