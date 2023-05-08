#pragma once

#include <iostream>
#include <conio.h>

#include "../outstream/outputControl.h"
#include "instreamBuffer.h"
#include "../system/system.h"

#define INSCharToStr INStreamBuffer::charToStr

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
	static void controlKeyHandler(char charInput, INStreamBuffer& lineInput, bool& end);
	static std::string formatString(std::string text, int cursorPos);	

	static inline void updateConsoleInput(const INStreamBuffer& lineInput) noexcept {
		sysprint(delWindow());
		sysprint(formatString(lineInput, lineInput.getCursorIndex()));
	}
};