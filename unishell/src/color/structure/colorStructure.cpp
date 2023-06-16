#include "colorStructure.h"


Color stringToColor(const std::string& strMode)
{
	if (strMode == "std") return null;

	if (strMode == "red") return red;
	if (strMode == "green") return green;
	if (strMode == "yellow") return yellow;
	if (strMode == "blue") return blue;
	if (strMode == "purple") return purple;
	if (strMode == "cyan") return cyan;
	if (strMode == "white") return white;

	if (strMode == "gray") return gray;
	if (strMode == "wred") return wred;
	if (strMode == "wgreen") return wgreen;
	if (strMode == "wyellow") return wyellow;
	if (strMode == "wblue") return wblue;
	if (strMode == "wpurple") return wpurple;
	if (strMode == "wcyan") return wcyan;

	return null;
}

ColorMode stringToColorMode(const std::string& strMode)
{
	if (strMode == "normal") return normal;
	if (strMode == "dark") return dark;
	if (strMode == "italic") return italic;
	if (strMode == "underline") return underline;
	if (strMode == "crossed") return crossed;

	return normal;
}
