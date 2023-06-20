#pragma once

#include <iostream>
#include <conio.h>

#include "../../outstream/control/control_chars.h"
#include "../../system/system.h"
#include "../../algorithm/vector/sort.h"
#include "../../algorithm/string/char.h"
#include "../../algorithm/bit/operations.h"

#include "list_buffer.h"
#include "search_list.h"
#include "buffer.h"


enum ASCIICode
{
	CarriageReturn =  13,
	Backspace      =   8,
	Tab            =   9,

	SpecialChar    = -32,

	UpArrow        =  72,
	DownArrow      =  80,
	LeftArrow      =  75,
	RightArrow     =  77,
};

enum KeyModifiers
{
	Control = 0x01,
	Shift   = 0x02,
	Alt     = 0x04
};


class INStream
{
public:
	static std::string getLine();

private:
	friend class INStreamRender;


	static int getPressedModifiers() noexcept {
		int modifiers = 0;

		if (alg::bit::hasBits(GetAsyncKeyState(VK_LCONTROL), 0x8000))	modifiers |= Control;
		if (alg::bit::hasBits(GetAsyncKeyState(VK_LSHIFT), 0x8000))		modifiers |= Shift;
		if (alg::bit::hasBits(GetAsyncKeyState(VK_LMENU), 0x8000))		modifiers |= Alt;

		return modifiers;	
	}
	
	static int getKeyPressedWhileCtrlPressed() {
		for (int i = 0; i < 256; i++) {
			const int state = (GetAsyncKeyState(i) & 0x8000);

			if (keyIsNotCtrlVK(i) && state == 0x8000)
				return (keyWithCtrlIsValid(i)) ? i : 0;
		}

		return 0;
	}

	static constexpr bool keyIsNotCtrlVK(const int key) {
		return (!alg::vector::exists({
			VK_CONTROL, VK_LCONTROL, VK_RCONTROL
		}, key));
	}

	// ctrl + "keys" that already has its functionality
	static constexpr bool keyWithCtrlIsValid(const int key) {
		return (!alg::vector::exists({
			VK_CONTROL, 'V'
		}, key));
	}


	static INSListBuffer inputList;
	static INSSearchList searchList;

	static void updateSearchList(const INStreamBuffer& buffer, const int begin, const int end) noexcept {
		if (!searchList.sequence) {
			int _begin = begin, _end = end;

			if (searchList.getType() == SearchListType::Files && buffer[begin] == '\"' && buffer[end] == '\"')
				_begin++, _end--;

			searchList.set(alg::vector::sortByCharacters(searchList.getList(), buffer.substr(_begin, _end - _begin + 1)));
		}
	}

	static void insertAtINStreamBuffer(INStreamBuffer& buffer, const std::string& item, const int begin, const int end) {
		buffer.erase(begin, end - begin + 1);
		buffer.insert(begin + ((!begin || begin + 1 > buffer.size()) ? 0 : 1), item);
		buffer.setCursorIndex((int)buffer.size());
	}

	// gets the color of enclose characters based on scope
	static BaseColorStructure* getEncloseColorByScope(const int scope) {
		if (scope == 1) return __clr_encloses_s1;
		if (scope == 2) return __clr_encloses_s2;
		if (scope == 3) return __clr_encloses_s3;
		if (scope >= 4) return __clr_encloses_s4;

		return __clr_encloses_s4;
	}

	static void controlKeyHandler(char charInput, INStreamBuffer& lineInput, bool& end);
	static std::string formatString(const std::string& text, const int cursorPos);	

	static void updateConsoleInput(const INStreamBuffer& lineInput, const bool drawCursor = true) noexcept {
		sysprint(delWindow() + formatString(lineInput, ((drawCursor) ? lineInput.getCursorIndex() : -1)));
	}

	constexpr static bool isValidForNum(const char ch) noexcept {
		return (alg::string::isDigit(ch) || alg::string::isWordSeparator(ch));
	}
};