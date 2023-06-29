#pragma once

#include "type.h"
#include "../../filesystem/formating/formating.h"
#include "../../system/windows/system_memory.h"

#include <regex>

namespace lit
{
	LiteralValue* newFileDataObj(const std::string& fileName, const std::string& fileEx, const int size, const fsys::FileF::FileAtts& atts) noexcept;
	
	LiteralValue* newRegexResultObj(std::smatch& match);

	LiteralValue* newSysMemStatObj(const SystemMemoryInfo& memInfo);
	LiteralValue* newSysDiskStatObj(const SystemDiskInfo& diskInfo);
}