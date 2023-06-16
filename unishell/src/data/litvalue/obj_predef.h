#pragma once

#include "type.h"
#include "../../filesystem/formating/fileFormatting.h"

#include <regex>

namespace lit
{
	LiteralValue* newFileDataObj(const std::string& fileName, const std::string& fileEx, const int size, const fsys::FileF::FileAtts& atts) noexcept;
	
	LiteralValue* newRegexResultObj(std::smatch& match);
}