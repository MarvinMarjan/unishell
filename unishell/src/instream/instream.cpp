#include "instream.h"

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
	switch ((int) charInput)
	{
	case CarriageReturn:
		sysprintln("");
		end = true;
		break;

	case Backspace:
		lineInput.eraseAtIndex(lineInput.getCursorIndex() - 1);
		updateConsoleInput(lineInput);
		
		break;

	// special characters have two codes, 
	// one to identify the character as special and another to be the code of the character itself
	case SpecialChar:
		charInput = _getch(); // each code is consumed individually, so you need to consume twice

		// TODO: arrow character processing
		if (charInput == UpArrow)
		{
		}

		else if (charInput == DownArrow)
		{
		}

		else if (charInput == LeftArrow && lineInput.getCursorIndex() > 0)
			lineInput.cursorLeft();

		else if (charInput == RightArrow && lineInput.getCursorIndex() < lineInput.size())
			lineInput.cursorRight();

		updateConsoleInput(lineInput);
		break;

	default:
		lineInput.insertStr(lineInput.getCursorIndex(), INSCharToStr(charInput));
		updateConsoleInput(lineInput);
	}
}

std::string INStream::formatString(std::string text, int cursorPos)
{
	std::string formatedStr = "";

	if (cursorPos >= text.size())
		text += clr("_", 75);

	else {
		char buff = text[cursorPos];
		text = text.erase(cursorPos, 1);
		text.insert(cursorPos, clr(INSCharToStr(buff), 75, underline));
	}

	formatedStr = text;

	return formatedStr;
}