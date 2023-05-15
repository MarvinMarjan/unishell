#pragma once

#include "instreamBuffer.h"
#include "../outstream/outputColor.h"



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
			INStreamRender::renderChar(i, cursorPos, text[i], stream, StringUtil::charToStr(text[i]), id(141));
		
		stream << endclr; // end color rendering
	}

	// quoted string: "hello, world"
	static inline void renderQuoted(std::stringstream* stream, const std::string& text, char current, size_t& i, int cursorPos) {
		INStreamRender render(stream, cursorPos);

		render.renderChar(i, current, id(106) + current, id(106)); // draw first quote

		while (text[++i] != '\"' && i < text.size())
			render.renderChar(i, text[i], StringUtil::charToStr(text[i]), id(106));

		render.renderChar(i, text[i], StringUtil::charToStr(text[i]) + endclr, ""); // draw last quote
	}

	// indentifier: $indentifier
	static inline void renderIndentifier(std::stringstream& stream, const std::string& text, char current, size_t& i, int cursorPos) {
		stream << id(115);

		INStreamRender::renderChar(i, cursorPos, current, stream, StringUtil::charToStr(text[i]), id(115));

		while (StringUtil::isAlphaNumeric(text[++i]))
			INStreamRender::renderChar(i, cursorPos, text[i], stream, StringUtil::charToStr(text[i]), id(115));

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
