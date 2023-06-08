#include "exceptionReference.h"

#include "system.h"

ExceptionRef::ExceptionRef() {
	src = *System::input();
	index = -1;
}

ExceptionRef::ExceptionRef(const std::string& src, int index) :
	src(src), index(index) {}

ExceptionRef::ExceptionRef(const std::string& src, size_t index) :
	src(src), index((int)index) {}

std::string ExceptionRef::getString() const {
	std::string str = "", space = "\n";
	const std::string atLoc = "  at " + clr('\"' + src + '\"', 113) + "\n\n";

	if (index != -1) {
		for (size_t i = 0; i < src.size(); i++)
			str += ((i == index) ? clr(StringUtil::charToStr(src[i]), 196) : StringUtil::charToStr(src[i]));

		for (size_t i = 0; i < index; i++) space += ' ';

		space += clr("^", 196);
	}

	if (str.empty()) space = "";

	return atLoc + str + space;
}