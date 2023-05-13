#include "instream.h"

#include <sstream>

INSListBuffer INStream::globalInputList = INSListBuffer();

// user input
std::string INStream::getLine()
{
	INStreamBuffer lineInput;
	char charInput;

	bool end = false;

	sysprint(saveCursor());

	while (!end)
	{
		sysprint(loadCursor());

		charInput = _getch();

		controlKeyHandler(charInput, lineInput, end);
	}

	return lineInput;
}

// process control keys
void INStream::controlKeyHandler(char charInput, INStreamBuffer& lineInput, bool& end)
{
	// reset input list current index
	if ((int)charInput != SpecialChar)
		globalInputList.reset();

	switch ((int)charInput)
	{
	case CarriageReturn:
		updateConsoleInput(lineInput, false);
		globalInputList.add(lineInput);
		sysprintln(""); // new line
		end = true;
		break;

	case Backspace:
		lineInput.eraseAtIndex(lineInput.getCursorIndex() - 1); // erase the character before cursor
		updateConsoleInput(lineInput);
		
		break;

	// special characters have two codes, 
	// one to identify the character as special and another to be the code of the character itself
	case SpecialChar:
		charInput = _getch(); // each code is consumed individually, so you need to consume twice

		if (charInput == UpArrow) {
			globalInputList.up();
			lineInput.assign(globalInputList.get());
			lineInput.setCursorIndex(lineInput.size());
		}
		
		// don't allow DownArrow processing if ignoreCurrenIndexChange is true
		else if (charInput == DownArrow && !globalInputList.ignoreCurrentIndexChange) {
			globalInputList.down();
			lineInput.assign(globalInputList.get());
			lineInput.setCursorIndex(lineInput.size());
		}

		else if (charInput == LeftArrow)
			lineInput.cursorLeft();

		else if (charInput == RightArrow)
			lineInput.cursorRight();

		updateConsoleInput(lineInput);
		break;

	default:
		lineInput.insertStr(lineInput.getCursorIndex(), UTCharToStr(charInput));
		updateConsoleInput(lineInput);
	}
}

// format string
std::string INStream::formatString(std::string text, int cursorPos)
{
	const std::string srcText = text;
	std::stringstream fText;
	size_t firstWordSize = StringUtil::split(text)[0].size();

	for (size_t i = 0; i < text.size(); i++)
	{
		INStreamRender::renderCommand(fText, text, cursorPos, i, firstWordSize);

		char current = text[i];

		switch (current)
		{
		case '\"':
			INStreamRender::renderQuoted(&fText, text, current, i, cursorPos);
			break;

		default:
			INStreamRender::renderChar(i, cursorPos, text[i], fText, UTCharToStr(text[i]));
		}
	}

	// cursor is at end of the text
	if (cursorPos >= text.size() && cursorPos != -1)
		fText << INSCursor('_');
	
	return fText.str();
}