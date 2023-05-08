#pragma once

#include "instreamBuffer.h"
#include "../outstream/outputColor.h"

#include <sstream>

#define INSCursor INStreamRender::cursor

class INStreamRender
{
private:
	friend class INStream;

	INStreamRender(std::stringstream* stream, int cursorPos) : renderStream(stream), cursorPos(cursorPos) {}

	// returns a string that represents a cursor. "after" is the string that will be drawed after cursor
	static inline std::string cursor(char ch, std::string after = endclr) noexcept {
		return clr(INSCharToStr(ch), 75, underline) + after;
	}


	static inline void renderCommand(size_t& i, int cursorPos, size_t firstWordSize, const std::string& text, std::stringstream& stream) {
		if (i >= firstWordSize) return;

		for (i; i < firstWordSize; i++)
			INStreamRender::renderChar(i, cursorPos, text[i], stream, id(141) + text[i]);	
		
		stream << endclr;
	}

	// quoted string: "hello, world"
	static inline void renderQuoted(std::stringstream* stream, const std::string& text, char current, size_t& i, int cursorPos) {
		INStreamRender render(stream, cursorPos);
		render.renderChar(i, current, id(106) + current, id(106));

		while (text[++i] != '\"' && i < text.size())
			render.renderChar(i, text[i], INSCharToStr(text[i]), id(106));

		render.renderChar(i, text[i], INSCharToStr(text[i]) + endclr, "");
	}

	// draws a cursor if currentPos equals to cursorPos.
	// "stream" is the drawing stringstream, "cursorChar" is the character of the cursor, 
	// "defaultValue" is the value to be drawed if currentPos not equals to cursorPos.
	// "after" has same meaning of INStreamRender::cursor

	static inline void renderChar(size_t currentPos, int cursorPos, char cursorChar, std::stringstream& stream,
		std::string defaultValue, std::string after = endclr)
	{
		if (currentPos == cursorPos)
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
