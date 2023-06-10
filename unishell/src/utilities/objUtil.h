#pragma once

#include "../parser/expression/type.h"
#include "../filesystem/fileFormatting.h"

#include "regexUtil.h"

class ObjUtil
{
public:
	static LiteralValue* newFileDataObj(
		const std::string& fileName, const std::string& fileEx, const int size, const fsys::FileF::FileAtts& atts
	) noexcept 
	{
		return lit(LitObj({
			{"name", lit(fileName)},
			{"ex", lit(fileEx)},
			{"size", lit(size)},
			{"att", lit(LitObj({
				{"archive", lit(atts.archive)},
				{"compressed", lit(atts.compressed)},
				{"device", lit(atts.device)},
				{"directory", lit(atts.directory)},
				{"ea", lit(atts.ea)},
				{"encrypted", lit(atts.encrypted)},
				{"hidden", lit(atts.hidden)},
				{"integrityStream", lit(atts.integrityStream)},
				{"normal", lit(atts.normal)},
				{"notContentIndexed", lit(atts.notContentIndexed)},
				{"noScrubData", lit(atts.noScrubData)},
				{"offline", lit(atts.offline)},
				{"pinned", lit(atts.pinned)},
				{"readOnly", lit(atts.readOnly)},
				{"recallOnDataAccess", lit(atts.recallOnDataAccess)},
				{"recallOnOpen", lit(atts.recallOnOpen)},
				{"reparsePoint", lit(atts.reparsePoint)},
				{"sparseFile", lit(atts.sparseFile)},
				{"system", lit(atts.system)},
				{"strictlySequential", lit(atts.strictlySequential)},
				{"temporary", lit(atts.temporary)},
				{"virt", lit(atts.virt)},
			}))}
		}));
	}

	static LiteralValue* newRegexResult(std::smatch& match) {
		LiteralValue* list = lit(LitList());

		if (match.size())
			asObj(list).insert({ "full", lit(match[0])});

		asObj(list).insert({ "group", lit(LitList()) });

		for (size_t i = 1; i < match.size(); i++)
			asList(asObj(list).at("group")).push_back(lit(match[i].str()));

		return list;
	}
};