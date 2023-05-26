#pragma once

#include <iostream>
#include <conio.h>

#include "../outstream/outputControl.h"
#include "../system/system.h"

#include "instreamRender.h"
#include "instreamListBuffer.h"


enum ASCIICode
{
	CarriageReturn =  13,
	Backspace      =   8,

	SpecialChar    = -32,

	UpArrow        =  72,
	DownArrow      =  80,
	LeftArrow      =  75,
	RightArrow     =  77
};

class INStream
{
public:
	static std::string getLine();

private:
	friend class INStreamRender;

	static INSListBuffer globalInputList; // global

	static inline BaseColorStructure* getEncloseColorByScope(int scope) {
		if (scope == 1) return __clr_encloses_s1;
		if (scope == 2) return __clr_encloses_s2;
		if (scope == 3) return __clr_encloses_s3;
		if (scope >= 4) return __clr_encloses_s4;

		return __clr_encloses_s4;
	}

	static void controlKeyHandler(char charInput, INStreamBuffer& lineInput, bool& end);
	static std::string formatString(const std::string& text, int cursorPos);	

	static inline void updateConsoleInput(const INStreamBuffer& lineInput, bool drawCursor = true) noexcept {
		sysprint(delWindow() + formatString(lineInput, ((drawCursor) ? lineInput.getCursorIndex() : -1)));
	}

	constexpr static inline bool isValidForNum(char ch) noexcept {
		return (StringUtil::isDigit(ch) || StringUtil::isWordSeparator(ch));
	}
};