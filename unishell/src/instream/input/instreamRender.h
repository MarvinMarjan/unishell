#pragma once

#include "instreamBuffer.h"
#include "instream.h"

#include "../../outstream/color/colorChars.h"
#include "../../instream/scanner/instreamScanner.h"
#include "../../color/parser/colorParser.h"
#include "../../system/global/global.h"

#define INSCursor INStreamRender::cursor

class INStreamRender
{
private:
	friend class INStream;

	// returns a string that represents a cursor. "after" is the string that will be drawed after cursor
	static std::string cursor(const char ch, const std::string& after = endclr) noexcept {
		return clr(alg::string::charToStr(ch), __clr_cursor->toString()) + after;
	}



	static void renderAutocompleteSuggestion(std::stringstream& stream, const std::string& text, const int cursorPos, size_t i);

	// command string
	static void renderCommand(std::stringstream& stream, const std::string& text, const int cursorPos, size_t& i, const size_t firstWordPos);

	static void renderRetCommand(std::stringstream& stream, const std::string& text, size_t& i, const int cursorPos);

	// quoted string: "hello, world"
	static void renderQuoted(std::stringstream& stream, const std::string& text, size_t& i, const int cursorPos);

	static void renderRawString(std::stringstream& stream, const std::string& text, size_t& i, const int cursorPos);

	// indentifier: $indentifier
	static void renderIdentifier(std::stringstream& stream, const std::string& text, size_t& i, const int cursorPos);
	
	// keywords that exists in __keywords
	static bool renderKeyword(std::stringstream& stream, const std::string& text, size_t& i, const int cursorPos);

	// render boolean values (true | false)
	static bool renderBoolean(std::stringstream& stream, const std::string& text, size_t& i, const int cursorPos);

	// render a color syntax with the color that the syntax represents.
	// i.e: id:205;underline: | clr:red: | rgb:100;100;100;italic:
	static bool renderColor(std::stringstream& stream, const std::string& text, size_t& i, const int cursorPos);

	static void renderWord(std::stringstream& stream, const std::string& text, size_t& i, const int cursorPos, BaseColorStructure* color, bool digit = false) noexcept;

	static void renderUntil(std::stringstream& stream, const std::string& text, size_t& i, const int cursorPos, const BaseColorStructure* const color, size_t until, bool decrement = true);


	// draws a cursor if currentPos equals to cursorPos.
	// "stream" is the drawing stringstream, "cursorChar" is the character of the cursor, 
	// "defaultValue" is the value to be drawed if currentPos not equals to cursorPos.
	// "after" has same meaning of INStreamRender::cursor

	static void renderChar(const size_t currentPos, const int cursorPos, char cursorChar, std::stringstream& stream, const std::string& defaultValue, const std::string& after = endclr)
	{
		if (currentPos == cursorPos && cursorPos != -1)
			stream << cursor(cursorChar, after);

		else
			stream << defaultValue;
	}

	static size_t getWordEndPos(const std::string& text, size_t pos = 0, bool ignoreQuote = true);

	static size_t getWordBeginPos(const std::string& text, size_t pos = 0, bool ignoreQuote = true);
};