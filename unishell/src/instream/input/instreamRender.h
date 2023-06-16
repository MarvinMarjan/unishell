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

	static void renderAutocompleteSuggestion(std::stringstream& stream, const std::string& text, const int cursorPos, size_t i) {
		if (cursorPos != -1 && cursorPos > text.size() - 1 && i + 1 >= text.size()) {
			const int begin = (int)INStreamRender::getWordBeginPos(text, ((cursorPos == 0) ? cursorPos : cursorPos - 1));

			std::string lastWord = text.substr(begin, cursorPos - begin);

			StringList tempSearchList = alg::vector::sortByCharacters(INStream::searchList.getList(), lastWord);

			if (tempSearchList.size() == 1 && lastWord.size() <= tempSearchList[0].size())
				stream << clr(tempSearchList[0].substr(lastWord.size()), __clr_autocomplete_suggestion->toString());
		}
	}

	// command string
	static void renderCommand(std::stringstream& stream, const std::string& text, const int cursorPos, size_t& i, const size_t firstWordPos)
	{
		const std::string cmdName = std::string(text.begin(), text.begin() + firstWordPos + 1);
		const CommandBase* const cmd = getCommand(cmdName);

		BaseColorStructure* commandClr = commandClr = getCommandColor(__sys_commands, cmdName);

		renderUntil(stream, text, i, cursorPos, commandClr, firstWordPos);
	}

	static void renderRetCommand(std::stringstream& stream, const std::string& text, size_t& i, const int cursorPos) {
		BaseColorStructure* retCmdColor = __clr_command;

		if (i + 1 < text.size()) {
			std::string cmdName = std::string(text.begin() + i, text.begin() + getWordEndPos(text, i + 1) + 1);
			
			if (!alg::string::isAlpha(cmdName[0]))
				cmdName = cmdName.substr(1);
			
			retCmdColor = getCommandColor(__sys_ret_commands, cmdName);
		}

		renderWord(stream, text, i, cursorPos, retCmdColor, true);
	}

	// quoted string: "hello, world"
	static void renderQuoted(std::stringstream& stream, const std::string& text, size_t& i, const int cursorPos) {
		stream << __clr_quoted->toString();

		renderChar(i, cursorPos, text[i], stream, alg::string::charToStr(text[i]), __clr_quoted->toString()); // draw first quote

		while (text[++i] != '\"' && i < text.size()) {
			if (text[i] == '\\' && i + 1 < text.size()) {
				renderChar(i, cursorPos, text[i], stream, __clr_escape_char->toString() + alg::string::charToStr(text[i]) , __clr_escape_char->toString());
				i++;
				renderChar(i, cursorPos, text[i], stream, alg::string::charToStr(text[i]), __clr_escape_char->toString());
				stream << __clr_quoted->toString();
			}
			else
				renderChar(i, cursorPos, text[i], stream, alg::string::charToStr(text[i]), __clr_quoted->toString());
		}

		renderChar(i, cursorPos, text[i], stream, alg::string::charToStr(text[i]), ""); // draw last quote

		stream << endclr;
	}

	static void renderRawString(std::stringstream& stream, const std::string& text, size_t& i, const int cursorPos) {
		stream << __clr_raw_string->toString();

		renderChar(i, cursorPos, text[i], stream, alg::string::charToStr(text[i]), __clr_raw_string->toString()); // draw first char

		while (text[++i] != '`' && i < text.size())
			renderChar(i, cursorPos, text[i], stream, alg::string::charToStr(text[i]), __clr_raw_string->toString());

		renderChar(i, cursorPos, text[i], stream, alg::string::charToStr(text[i]), ""); // draw last char

		stream << endclr;
	}

	// indentifier: $indentifier
	static void renderIdentifier(std::stringstream& stream, const std::string& text, size_t& i, const int cursorPos) {
		BaseColorStructure* idColor = __clr_identifier;

		if (i + 1 < text.size()) {
			const std::string idName = std::string(text.begin() + i, text.begin() + getWordEndPos(text, i + 1) + 1);
			const Identifier* const id = System::env()->getId(idName);

			if (id) idColor = __clr_ex_identifier;

			if (id && id->isSysId()) idColor = __clr_ex_sys_identifier;
		}

		renderWord(stream, text, i, cursorPos, idColor, true);
	}
	
	// keywords that exists in __keywords
	static bool renderKeyword(std::stringstream& stream, const std::string& text, size_t& i, const int cursorPos) {
		size_t aux = i;

		if (alg::string::isAlphaNumeric(text[aux - 1])) return false;

		while (alg::string::isAlpha(text[aux])) aux++;

		if (alg::vector::exists(__keywords, text.substr(i, aux - i))) {
			renderWord(stream, text, i, cursorPos, __clr_keyword);
			return true;
		}

		return false;
	}

	// render boolean values (true | false)
	static bool renderBoolean(std::stringstream& stream, const std::string& text, size_t& i, const int cursorPos) {
		size_t aux = i;

		if (alg::string::isAlphaNumeric(text[aux - 1])) return false;

		while (alg::string::isAlpha(text[aux])) aux++;

		if (alg::vector::exists(__boolean, text.substr(i, aux - i))) {
			renderWord(stream, text, i, cursorPos, __clr_boolean);
			return true;
		}

		return false;
	}

	// render a color syntax with the color that the syntax represents.
	// i.e: id:205;underline: | clr:red: | rgb:100;100;100;italic:
	static bool renderColor(std::stringstream& stream, const std::string& text, size_t& i, const int cursorPos) {
		size_t start = i, end = 0, aux = i;

		while (text[aux] != ':')
			if (!alg::string::isAlpha(text[aux++])) return false;

		if (!alg::vector::exists(__color_formats, std::string(text.begin() + start, text.begin() + aux))) return false;
		if (++aux >= text.size()) return false;
		
		while (text[aux] != ':')
			if (++aux >= text.size()) return false;

		end = aux;

		const TokenList tokens = InstreamScanner(std::string(text.begin() + start, text.begin() + end + 1), IgnoreCommand).scanTokens();
		const BaseColorStructure* const color = ColorParser(tokens, true).parse();

		// if color is valid
		if (color)
			renderUntil(stream, text, i, cursorPos, color, end);
		
		return (color) ? true : false;
	}

	static void renderWord(std::stringstream& stream, const std::string& text, size_t& i,
		const int cursorPos, BaseColorStructure* color, bool digit = false) noexcept
	{
		// render color
		stream << color->toString();

		// render first char
		renderChar(i, cursorPos, text[i], stream, alg::string::charToStr(text[i]), color->toString());

		while (alg::string::isAlpha(text[++i]) || (alg::string::isDigit(text[i]) && digit))
			renderChar(i, cursorPos, text[i], stream, alg::string::charToStr(text[i]), color->toString());

		i--; // necessary to dis-ignore next char

		stream << endclr;
	}

	static void renderUntil(std::stringstream& stream, const std::string& text, size_t& i,
		const int cursorPos, const BaseColorStructure* const color, size_t until, bool decrement = true)
	{
		stream << color->toString();

		for (i; i <= until; i++)
			renderChar(i, cursorPos, text[i], stream, alg::string::charToStr(text[i]), color->toString());

		if (decrement) i--;

		stream << endclr;
	}

	// draws a cursor if currentPos equals to cursorPos.
	// "stream" is the drawing stringstream, "cursorChar" is the character of the cursor, 
	// "defaultValue" is the value to be drawed if currentPos not equals to cursorPos.
	// "after" has same meaning of INStreamRender::cursor

	static void renderChar(const size_t currentPos, const int cursorPos, char cursorChar, std::stringstream& stream,
		const std::string& defaultValue, const std::string& after = endclr)
	{
		if (currentPos == cursorPos && cursorPos != -1)
			stream << cursor(cursorChar, after);

		else
			stream << defaultValue;
	}

	static size_t getWordEndPos(const std::string& text, size_t pos = 0, bool ignoreQuote = true) {
		if (text[pos] == '\"' && !ignoreQuote) {
			while (text[++pos] != '\"') {}
			return pos;
		}

		do {
			if (pos >= text.size() - 1 && alg::string::isAlphaNumeric(text[pos]))
				return pos;
		}
		while (alg::string::isAlphaNumeric(text[pos++]));
		pos--;

		if (pos > 0) pos--;
		return pos;
	}

	static size_t getWordBeginPos(const std::string& text, size_t pos = 0, bool ignoreQuote = true) {
		if (text[pos] == '\"' && !ignoreQuote) {
			while (text[--pos] != '\"') {}
			return pos;
		}

		do {
			if (pos <= 0 && alg::string::isAlphaNumeric(text[pos]))
				return pos;
		}
		while (alg::string::isAlphaNumeric(text[pos--]));
		pos++;

		if (pos + 1 < text.size()) pos++;
		return pos;
	}
};
