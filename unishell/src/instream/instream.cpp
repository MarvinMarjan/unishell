#include "instream.h"


INSListBuffer INStream::inputList = INSListBuffer();
INSSearchList INStream::searchList = INSSearchList();

// process control keys
void INStream::controlKeyHandler(char charInput, INStreamBuffer& lineInput, bool& end)
{
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
		int begin = INStreamRender::getWordBeginPos(lineInput, lineInput.getCursorIndex() - 1);
		int end = INStreamRender::getWordEndPos(lineInput, lineInput.getCursorIndex() - 1);

		if (begin + 1 < lineInput.size()) begin++;

		if (!searchList.sequence)
			searchList.set(VectorUtil::sortByCharacters(searchList.getList(), lineInput.substr(begin, end - begin + 1)));

		std::string str = searchList.get();

		lineInput.erase(lineInput.begin() + begin, lineInput.begin() + end + 1);
		lineInput.insert(begin, str);

		lineInput.setCursorIndex((int)lineInput.size());

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
		
		// don't allow DownArrow processing if ignoreCurrenIndexChange is true
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
	size_t firstWordPos = INStreamRender::getWordEndPos(text);
	int scopeDepth = 1;

	for (size_t i = 0; i < text.size(); i++)
	{
		if (i <= firstWordPos) {
			INStreamRender::renderCommand(fText, text, cursorPos, i, firstWordPos);
			searchList.set(__sys_commands);
		}

		char current = text[i];

		switch (current)
		{
		case ' ':
		case '\t':
			INStreamRender::renderChar(i, cursorPos, text[i], fText, StringUtil::charToStr(text[i]));
			break;

		case '\"':
			INStreamRender::renderQuoted(fText, text, i, cursorPos);
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

		case '$':
			INStreamRender::renderIdentifier(fText, text, i, cursorPos);
			break;

		case '@':
		case '#':
			INStreamRender::renderRetCommand(fText, text, i, cursorPos);
			break;

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
	}

	// cursor is at end of the text
	if (cursorPos >= text.size() && cursorPos != -1)
		fText << INSCursor('_');
	
	return fText.str();
}