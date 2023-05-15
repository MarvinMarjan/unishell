#pragma once

#include "../utilities/stringUtil.h"
#include "../outstream/outputColor.h"

class ExceptionRef
{
public:
	ExceptionRef(const std::string& src, unsigned int index = 0) : src(src), index(index) {}

	inline std::string getString() const {
		std::string str = "";
		std::string space = "";

		for (size_t i = 0; i < src.size(); i++) 
			str += ((i == index) ? clr(StringUtil::charToStr(src[i]), 196) : StringUtil::charToStr(src[i]));

		for (size_t i = 0; i < index; i++) space += ' ';
		
		space += clr("^", 196);

		return std::string("  at ") + clr('\"' + src + '\"', 113) + "\n\n" + str + ((str.empty()) ? "" : '\n' + space);
	}

private:
	std::string src;
	unsigned int index;
};
