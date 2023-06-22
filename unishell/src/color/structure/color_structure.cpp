#include "color_structure.h"


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

std::string colorEnumToString(const Color color)
{
	switch (color)
	{
	case null:      return "std";
	case red:       return "red";
	case green:     return "green";
	case yellow:    return "yellow";
	case blue:      return "blue";
	case purple:    return "purple";
	case cyan:      return "cyan";
	case white:     return "white";
	case gray:      return "gray";
	case wred:      return "wred";
	case wgreen:    return "wgreen";
	case wyellow:   return "wyellow";
	case wblue:     return "wblue";
	case wpurple:   return "wpurple";
	case wcyan:     return "wcyan";
	}

	return "";
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

std::string colorModeEnumToString(const ColorMode mode)
{
	switch (mode)
	{
	case normal:	return "normal";
	case dark:		return "dark";
	case italic:	return "italic";
	case underline: return "underline";
	case crossed:	return "crossed";

	default:		return "normal";
	}
}