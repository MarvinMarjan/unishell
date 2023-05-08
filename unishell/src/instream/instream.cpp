#include "instream.h"

#include <sstream>

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
	const std::string srcText = text;
	std::stringstream fText;
	size_t firstWordSize = INStreamBuffer::split(text)[0].size();

	for (size_t i = 0; i < text.size(); i++)
	{
		INStreamRender::renderCommand(i, cursorPos, firstWordSize, text, fText);

		char current = text[i];

		switch (current)
		{
		case '\"':
			INStreamRender::renderQuoted(&fText, text, current, i, cursorPos);
			break;

		default:
			INStreamRender::renderChar(i, cursorPos, text[i], fText, INSCharToStr(text[i]));
		}
	}

	// cursor is at end of the text
	if (cursorPos >= text.size())
		fText << INSCursor('_');
	
	return fText.str();
}