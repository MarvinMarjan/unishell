#pragma once

#include "instreamBuffer.h"

#include "../outstream/outputColor.h"
#include "../parser/instream/instrScanner.h"
#include "../parser/color/colorParser.h"
#include "../system/global.h"

#define INSCursor INStreamRender::cursor

class INStreamRender
{
private:
	friend class INStream;

	INStreamRender(std::stringstream* stream, int cursorPos) : renderStream(stream), cursorPos(cursorPos) {}

	// returns a string that represents a cursor. "after" is the string that will be drawed after cursor
	static inline std::string cursor(char ch, std::string after = endclr) noexcept {
		return clr(StringUtil::charToStr(ch), __clr_cursor->toString()) + after;
	}

	// command string
	static inline void renderCommand(std::stringstream& stream, const std::string& text, int cursorPos, size_t& i, size_t firstWordPos) {
		if (i >= firstWordPos) return;

		BaseColorStructure* commandClr = __clr_command;

		// start color rendering
		if (VectorUtil::exists(__sys_commands, std::string(text.begin(), text.begin() + firstWordPos)))
			commandClr = __clr_ex_command; // commands exists

		renderUntil(stream, text, i, cursorPos, commandClr, firstWordPos, false);
	}

	static inline void renderRetCommand(std::stringstream& stream, const std::string& text, size_t& i, int cursorPos) {
		BaseColorStructure* retCmdColor = __clr_ret_command;

		if (i + 1 < text.size()) {
			std::string cmdName = std::string(text.begin() + i, text.begin() + getWordEndPos(text, i + 1));
			
			if (!StringUtil::isAlpha(cmdName[0]))
				cmdName = cmdName.substr(1);

			if (VectorUtil::exists(__sys_ret_commands, cmdName))
				retCmdColor = __clr_ex_sys_ret_command;
		}

		renderWord(stream, text, i, cursorPos, retCmdColor, true);
	}

	// quoted string: "hello, world"
	static inline void renderQuoted(std::stringstream& stream, const std::string& text, size_t& i, int cursorPos) {
		stream << __clr_quoted->toString();

		renderChar(i, cursorPos, text[i], stream, StringUtil::charToStr(text[i]), __clr_quoted->toString()); // draw first quote

		while (text[++i] != '\"' && i < text.size()) {
			if (text[i] == '\\' && i + 1 < text.size()) {
				renderChar(i, cursorPos, text[i], stream, __clr_escape_char->toString() + StringUtil::charToStr(text[i]) , __clr_escape_char->toString());
				i++;
				renderChar(i, cursorPos, text[i], stream, StringUtil::charToStr(text[i]), __clr_escape_char->toString());
				stream << __clr_quoted->toString();
			}
			else
				renderChar(i, cursorPos, text[i], stream, StringUtil::charToStr(text[i]), __clr_quoted->toString());
		}

		renderChar(i, cursorPos, text[i], stream, StringUtil::charToStr(text[i]), ""); // draw last quote

		stream << endclr;
	}

	// indentifier: $indentifier
	static inline void renderIdentifier(std::stringstream& stream, const std::string& text, size_t& i, int cursorPos) {
		BaseColorStructure* idColor = __clr_identifier;

		if (i + 1 < text.size()) {
			std::string idName = std::string(text.begin() + i, text.begin() + getWordEndPos(text, i + 1));
			Identifier* id = System::env()->getId(idName);

			if (id) idColor = __clr_ex_identifier;

			if (id && id->isSysId()) idColor = __clr_ex_sys_identifier;
		}

		renderWord(stream, text, i, cursorPos, idColor, true);
	}
	
	// keywords that exists in __keywords
	static inline bool renderKeyword(std::stringstream& stream, const std::string& text, size_t& i, int cursorPos) {
		size_t aux = i;

		if (StringUtil::isAlphaNumeric(text[aux - 1])) return false;

		while (StringUtil::isAlpha(text[aux])) aux++;

		if (std::find(__keywords.begin(), __keywords.end(), text.substr(i, aux - i)) != __keywords.end()) {
			renderWord(stream, text, i, cursorPos, __clr_keyword);
			return true;
		}

		return false;
	}

	// render boolean values (true | false)
	static inline bool renderBoolean(std::stringstream& stream, const std::string& text, size_t& i, int cursorPos) {
		size_t aux = i;

		if (StringUtil::isAlphaNumeric(text[aux - 1])) return false;

		while (StringUtil::isAlpha(text[aux])) aux++;

		if (std::find(__boolean.begin(), __boolean.end(), text.substr(i, aux - i)) != __boolean.end()) {
			renderWord(stream, text, i, cursorPos, __clr_boolean);
			return true;
		}

		return false;
	}

	// render a color syntax with the color that the syntax represents.
	// i.e: id:205;underline: | clr:red: | rgb:100;100;100;italic:
	static inline bool renderColor(std::stringstream& stream, const std::string& text, size_t& i, int cursorPos) {
		size_t start = i, end = 0, aux = i;

		while (text[aux] != ':')
			if (!StringUtil::isAlpha(text[aux++])) return false;

		if (!VectorUtil::exists(__color_formats, std::string(text.begin() + start, text.begin() + aux))) return false;
		if (++aux >= text.size()) return false;
		
		while (text[aux] != ':')
			if (++aux >= text.size()) return false;

		end = aux;

		TokenList tokens = InstreamScanner(std::string(text.begin() + start, text.begin() + end + 1), IgnoreCommand).scanTokens();
		BaseColorStructure* color = ColorParser(tokens, true).parse();

		// if color is valid
		if (color)
			renderUntil(stream, text, i, cursorPos, color, end + 1);
		
		return (color) ? true : false;
	}

	static inline void renderWord(std::stringstream& stream, const std::string& text, size_t& i,
		int cursorPos, BaseColorStructure* color, bool digit = false) noexcept
	{
		// render color
		stream << color->toString();

		// render first char
		renderChar(i, cursorPos, text[i], stream, StringUtil::charToStr(text[i]), color->toString());

		while (StringUtil::isAlpha(text[++i]) || (StringUtil::isDigit(text[i]) && digit))
			renderChar(i, cursorPos, text[i], stream, StringUtil::charToStr(text[i]), color->toString());

		i--; // necessary to draw next char

		stream << endclr;
	}

	static inline void renderUntil(std::stringstream& stream, const std::string& text, size_t& i,
		int cursorPos, BaseColorStructure* color, size_t until, bool decrement = true) 
	{
		stream << color->toString();

		for (i; i < until; i++)
			renderChar(i, cursorPos, text[i], stream, StringUtil::charToStr(text[i]), color->toString());

		if (decrement) i--;

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

	static inline size_t getWordEndPos(const std::string& text, size_t pos = 0) {
		for (pos; StringUtil::isAlphaNumeric(text[pos]); pos++) {}

		return pos;
	}

	std::stringstream* renderStream = nullptr;
	int cursorPos;
};
