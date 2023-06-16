#pragma once

#include "../data/litvalue/type.h"
#include "../filesystem/formating/fileFormatting.h"

#include "regexUtil.h"

class ObjUtil
{
public:
	static lit::LiteralValue* newFileDataObj(
		const std::string& fileName, const std::string& fileEx, const int size, const fsys::FileF::FileAtts& atts
	) noexcept 
	{
		return lit::lit(lit::LitObject({
			{"name", lit::lit(fileName)},
			{"ex", lit::lit(fileEx)},
			{"size", lit::lit(size)},
			{"att", lit::lit(lit::LitObject({
				{"archive", lit::lit(atts.archive)},
				{"compressed", lit::lit(atts.compressed)},
				{"device", lit::lit(atts.device)},
				{"directory", lit::lit(atts.directory)},
				{"ea", lit::lit(atts.ea)},
				{"encrypted", lit::lit(atts.encrypted)},
				{"hidden", lit::lit(atts.hidden)},
				{"integrityStream", lit::lit(atts.integrityStream)},
				{"normal", lit::lit(atts.normal)},
				{"notContentIndexed", lit::lit(atts.notContentIndexed)},
				{"noScrubData", lit::lit(atts.noScrubData)},
				{"offline", lit::lit(atts.offline)},
				{"pinned", lit::lit(atts.pinned)},
				{"readOnly", lit::lit(atts.readOnly)},
				{"recallOnDataAccess", lit::lit(atts.recallOnDataAccess)},
				{"recallOnOpen", lit::lit(atts.recallOnOpen)},
				{"reparsePoint", lit::lit(atts.reparsePoint)},
				{"sparseFile", lit::lit(atts.sparseFile)},
				{"system", lit::lit(atts.system)},
				{"strictlySequential", lit::lit(atts.strictlySequential)},
				{"temporary", lit::lit(atts.temporary)},
				{"virt", lit::lit(atts.virt)},
			}))}
		}));
	}

	static lit::LiteralValue* newRegexResult(std::smatch& match) {
		lit::LiteralValue* list = lit::lit(lit::LitList());

		if (match.size())
			asObj(list).insert({ "full", lit::lit(match[0])});

		asObj(list).insert({ "group", lit::lit(lit::LitList()) });

		for (size_t i = 1; i < match.size(); i++)
			asList(asObj(list).at("group")).push_back(lit::lit(match[i].str()));

		return list;
	}
};