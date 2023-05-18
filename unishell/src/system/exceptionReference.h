#pragma once

#include "../utilities/stringUtil.h"
#include "../outstream/outputColor.h"

class ExceptionRef
{
public:
	ExceptionRef(const std::string& src, size_t index = 0) : src(src), index(index) {}

	// return a string containing error location information
	inline std::string getString() const {
		std::string str = "", space = "\n";
		std::string atLoc = "  at " + clr('\"' + src + '\"', 113) + "\n\n";

		for (size_t i = 0; i < src.size(); i++) 
			str += ((i == index) ? clr(StringUtil::charToStr(src[i]), 196) : StringUtil::charToStr(src[i]));

		for (size_t i = 0; i < index; i++) space += ' ';
		
		space += clr("^", 196);

		if (str.empty()) {
			atLoc = "";
			space = "";
		}

		return atLoc + str + space;
	}

private:
	std::string src;
	size_t index;
};
