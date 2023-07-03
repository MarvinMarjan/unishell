#include "exception_reference.h"

#include "../system.h"
#include "../../outstream/color/color_chars.h"

ExceptionRef::ExceptionRef() {
	src = *__userInput;
	index = -1;
}

ExceptionRef::ExceptionRef(const std::string& src, const int index) :
	src(src), index(index) {}

ExceptionRef::ExceptionRef(const std::string& src, const size_t index) :
	src(src), index((int)index) {}

ExceptionRef::ExceptionRef(const std::string& src, const Token& token) :
	src(src), index((int)token.getIndex()) {}



std::string ExceptionRef::getString() const {
	std::string str = "", space = "\n";
	const std::string atLoc = ((!src.empty()) ? "  at " + clr('\"' + src + '\"', 113) + "\n\n" : "");

	if (index != -1) {
		for (size_t i = 0; i < src.size(); i++)
			str += ((i == index) ? clr(alg::string::charToStr(src[i]), 196) : alg::string::charToStr(src[i]));

		for (size_t i = 0; i < index; i++)
			space += ' ';

		space += clr("^", 196);
	}

	if (str.empty()) space = "";

	return atLoc + str + space;
}