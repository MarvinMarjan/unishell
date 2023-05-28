#pragma once

#include "../parser/expression/type.h"
#include "fileUtil.h"

class ObjUtil
{
public:
	static inline LiteralValue* newFileDataObj(
		const std::string& fileName, const std::string& fileEx, int size, FileUtil::FileAtts atts) noexcept 
	{
		return litObj({
			{"name", litStr(fileName)},
			{"ex", litStr(fileEx)},
			{"size", litNum(size)},
			{"att", litObj({
				{"archive", litBool(atts.archive)},
				{"compressed", litBool(atts.compressed)},
				{"device", litBool(atts.device)},
				{"directory", litBool(atts.directory)},
				{"ea", litBool(atts.ea)},
				{"encrypted", litBool(atts.encrypted)},
				{"hidden", litBool(atts.hidden)},
				{"integrityStream", litBool(atts.integrityStream)},
				{"normal", litBool(atts.normal)},
				{"notContentIndexed", litBool(atts.notContentIndexed)},
				{"noScrubData", litBool(atts.noScrubData)},
				{"offline", litBool(atts.offline)},
				{"pinned", litBool(atts.pinned)},
				{"readOnly", litBool(atts.readOnly)},
				{"recallOnDataAccess", litBool(atts.recallOnDataAccess)},
				{"recallOnOpen", litBool(atts.recallOnOpen)},
				{"reparsePoint", litBool(atts.reparsePoint)},
				{"sparseFile", litBool(atts.sparseFile)},
				{"system", litBool(atts.system)},
				{"strictlySequential", litBool(atts.strictlySequential)},
				{"temporary", litBool(atts.temporary)},
				{"virt", litBool(atts.virt)},
			})}
		});
	}
};