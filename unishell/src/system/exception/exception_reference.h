#pragma once


#include "../../instream/scanner/instream_token.h"


class ExceptionRef
{
public:
	ExceptionRef();

	ExceptionRef(const std::string& src, const int index = -1);
	ExceptionRef(const std::string& src, const size_t index);
	ExceptionRef(const std::string& src, const Token& token);

	// return a string containing error location information
	std::string getString() const;

private:
	std::string src;
	int index;
};
