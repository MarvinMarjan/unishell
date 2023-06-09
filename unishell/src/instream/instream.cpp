#include "instream.h"
#include "instreamRender.h"

INSListBuffer INStream::inputList = INSListBuffer();
INSSearchList INStream::searchList = INSSearchList();

// process control keys
void INStream::controlKeyHandler(char charInput, INStreamBuffer& lineInput, bool& end)
{
	searchList.set(CmdUtil::cmdListToStr(__sys_commands));

	// reset input list current index if input is not a control char
	if ((int)charInput != SpecialChar)
		inputList.reset();

	if ((int)charInput != Tab)
		searchList.sequence = false;

	switch ((int)charInput)
	{
	case CarriageReturn:
		if (lineInput.empty()) break;
		updateConsoleInput(lineInput, false); // disable cursor rendering
		inputList.add(lineInput);
		sysprintln(""); // new line
		end = true;
		break;

	case Backspace:
		lineInput.eraseAtIndex(); // erase the character before cursor
		updateConsoleInput(lineInput);
		break;

	case Tab: {
		searchList.setFromType();

		const int cIndex = lineInput.getCursorIndex();

		if (searchList.getList().empty()) break;
		if (cIndex < lineInput.size()) break;

		const int begin = (int)INStreamRender::getWordBeginPos(lineInput, ((cIndex == 0) ? cIndex : cIndex - 1), false);
		const int end = (int)INStreamRender::getWordEndPos(lineInput, begin, false);

		updateSearchList(lineInput, begin, end);		
		insertAtINStreamBuffer(lineInput, searchList.get(), begin, end);

		searchList.next();
		searchList.sequence = true;

		updateConsoleInput(lineInput);
		break;
	}

	// special characters have two codes, 
	// one to identify the character as special and another to be the code of the character itself
	case SpecialChar:
		charInput = _getch(); // each code is consumed individually, so you need to consume twice

		if (charInput == UpArrow) {
			inputList.up();
			lineInput.assign(inputList.get());
			lineInput.setCursorIndex((int) lineInput.size());
		}
		
		// don't allow DownArrow processing if ignoreCurrentIndexChange is true
		else if (charInput == DownArrow && !inputList.ignoreCurrentIndexChange) {
			inputList.down();
			lineInput.assign(inputList.get());
			lineInput.setCursorIndex((int) lineInput.size());
		}

		else if (charInput == LeftArrow)
			lineInput.cursorLeft();

		else if (charInput == RightArrow)
			lineInput.cursorRight();

		updateConsoleInput(lineInput);
		break;

	default:
		lineInput.insertStr(lineInput.getCursorIndex(), StringUtil::charToStr(charInput));
		updateConsoleInput(lineInput);
	}
}

// format string
std::string INStream::formatString(const std::string& text, int cursorPos)
{
	std::stringstream fText;
	const size_t firstWordPos = INStreamRender::getWordEndPos(text);
	int scopeDepth = 1;

	for (size_t i = 0; i < text.size(); i++)
	{
		searchList.setType(SearchListType::Files);

		if (i <= firstWordPos) {
			searchList.setType(SearchListType::Command);
 			INStreamRender::renderCommand(fText, text, cursorPos, i, firstWordPos);
			INStreamRender::renderAutocompleteSuggestion(fText, text, cursorPos, i);
			continue;
		}

		const char current = text[i];

		switch (current)
		{
		case ' ':
		case '\t':
			INStreamRender::renderChar(i, cursorPos, text[i], fText, StringUtil::charToStr(text[i]));
			continue;

		case '\"':
			INStreamRender::renderQuoted(fText, text, i, cursorPos);
			break;

		case '`':
			INStreamRender::renderRawString(fText, text, i, cursorPos);
			break;

		case '(':
		case '{':
		case '[':
			// render first
			INStreamRender::renderChar(i, cursorPos, text[i], fText, clr(StringUtil::charToStr(text[i]), getEncloseColorByScope(scopeDepth)->toString()));

			scopeDepth++;

			break;

		case ')':
		case '}':
		case ']':
			// check first, then render
			scopeDepth--;
			if (scopeDepth < 1) scopeDepth = 1;
			
			INStreamRender::renderChar(i, cursorPos, text[i], fText, clr(StringUtil::charToStr(text[i]), getEncloseColorByScope(scopeDepth)->toString()));


			break;

		case '!':
		case '<':
		case '>':
		case '=':
		case '+':
		case '-':
		case '*':
		case '/':
			INStreamRender::renderChar(i, cursorPos, text[i], fText, clr(StringUtil::charToStr(text[i]), __clr_operators->toString()));
			break;

		// identifier rendering
		case '$':
			searchList.setType(SearchListType::Identifier);
			INStreamRender::renderIdentifier(fText, text, i, cursorPos);
			break;

		// RetCommand rendering
		case '@':
		case '#':
			searchList.setType(SearchListType::RetCommand);
			INStreamRender::renderRetCommand(fText, text, i, cursorPos);
			break;

		// flag rendering
		case '%':
			INStreamRender::renderWord(fText, text, i, cursorPos, __clr_flag, true);
			break;

		// other
		default:
			if (StringUtil::isDigit(text[i]) && isValidForNum(text[i - 1]) && ((i + 1 < text.size() && isValidForNum(text[i + 1])) || i + 1 >= text.size()))
			{
				for (i; StringUtil::isDigit(text[i]); i++)
					INStreamRender::renderChar(i, cursorPos, text[i], fText, clr(StringUtil::charToStr(text[i]), __clr_numbers->toString()));

				i--;
			}

			else if (!INStreamRender::renderKeyword(fText, text, i, cursorPos) &&
				     !INStreamRender::renderBoolean(fText, text, i, cursorPos) &&
					 !INStreamRender::renderColor(fText, text, i, cursorPos))
			{
				INStreamRender::renderChar(i, cursorPos, text[i], fText, StringUtil::charToStr(text[i]));
			}
		}

		if (i + 1 >= text.size())
			searchList.setFromType();

		INStreamRender::renderAutocompleteSuggestion(fText, text, cursorPos, i);
	}

	// cursor is at end of the text
	if (cursorPos >= text.size() && cursorPos != -1)
		fText << INSCursor('_');
	
	return fText.str();
}