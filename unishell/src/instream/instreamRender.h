#pragma once

#include "instreamBuffer.h"
#include "../outstream/outputColor.h"

#include "../system/global.h"

#define INSCursor INStreamRender::cursor

class INStreamRender
{
private:
	friend class INStream;

	INStreamRender(std::stringstream* stream, int cursorPos) : renderStream(stream), cursorPos(cursorPos) {}

	// returns a string that represents a cursor. "after" is the string that will be drawed after cursor
	static inline std::string cursor(char ch, std::string after = endclr) noexcept {
		return clr(StringUtil::charToStr(ch), 75, underline) + after;
	}

	// command string
	static inline void renderCommand(std::stringstream& stream, const std::string& text, int cursorPos, size_t& i, size_t firstWordSize) {
		if (i >= firstWordSize) return;

		stream << id(141); // start color rendering

		// draw command characters
		for (i; i < firstWordSize; i++)
			renderChar(i, cursorPos, text[i], stream, StringUtil::charToStr(text[i]), id(141));
		
		stream << endclr; // end color rendering
	}

	// quoted string: "hello, world"
	static inline void renderQuoted(std::stringstream& stream, const std::string& text, char current, size_t& i, int cursorPos) {
		stream << id(106);

		renderChar(i, cursorPos, text[i], stream, StringUtil::charToStr(text[i]), id(106)); // draw first quote

		while (text[++i] != '\"' && i < text.size())
			renderChar(i, cursorPos, text[i], stream, StringUtil::charToStr(text[i]), id(106));

		renderChar(i, cursorPos, text[i], stream, StringUtil::charToStr(text[i]), ""); // draw last quote

		stream << endclr;
	}

	// indentifier: $indentifier
	static inline void renderIndentifier(std::stringstream& stream, const std::string& text, char current, size_t& i, int cursorPos) {
		renderWord(stream, text, current, i, cursorPos, 115, true);
	}
	
	// keywords that exists in GBL_keywords
	static inline bool renderKeyword(std::stringstream& stream, const std::string& text, char current, size_t& i, int cursorPos) {
		size_t aux = i;

		if (StringUtil::isAlphaNumeric(text[aux - 1])) return false;

		while (StringUtil::isAlpha(text[aux])) aux++;

		if (std::find(GBL_keywords.begin(), GBL_keywords.end(), text.substr(i, aux - i)) != GBL_keywords.end()) {
			renderWord(stream, text, current, i, cursorPos, 128);
			return true;
		}

		return false;
	}

	// render boolean values (true | false)
	static inline bool renderBoolean(std::stringstream& stream, const std::string& text, char current, size_t& i, int cursorPos) {
		size_t aux = i;

		if (StringUtil::isAlphaNumeric(text[aux - 1])) return false;

		while (StringUtil::isAlpha(text[aux])) aux++;

		if (std::find(GBL_boolean.begin(), GBL_boolean.end(), text.substr(i, aux - i)) != GBL_boolean.end()) {
			renderWord(stream, text, current, i, cursorPos, 219);
			return true;
		}

		return false;
	}

	static inline void renderWord(std::stringstream& stream, const std::string& text, char current, size_t& i,
		int cursorPos, int idclr, bool digit = false) noexcept
	{
		// render color
		stream << id(idclr);

		// render first char
		renderChar(i, cursorPos, text[i], stream, StringUtil::charToStr(text[i]), id(idclr));

		while (StringUtil::isAlpha(text[++i]) || (StringUtil::isDigit(text[i]) && digit))
			renderChar(i, cursorPos, text[i], stream, StringUtil::charToStr(text[i]), id(idclr));

		i--; // necessary to draw next char

		stream << endclr;
	}

	// draws a cursor if currentPos equals to cursorPos.
	// "stream" is the drawing stringstream, "cursorChar" is the character of the cursor, 
	// "defaultValue" is the value to be drawed if currentPos not equals to cursorPos.
	// "after" has same meaning of INStreamRender::cursor

	static inline void renderChar(size_t currentPos, int cursorPos, char cursorChar, std::stringstream& stream,
		std::string defaultValue, std::string after = endclr)
	{
		if (currentPos == cursorPos && cursorPos != -1)
			stream << cursor(cursorChar, after);

		else
			stream << defaultValue;
	}

	inline void renderChar(size_t currentPos, char cursorChar, std::string defaultValue, std::string after = endclr) {
		if (currentPos == cursorPos)
			*renderStream << cursor(cursorChar, after);

		else
			*renderStream << defaultValue;
	}

	std::stringstream* renderStream = nullptr;
	int cursorPos;
};
