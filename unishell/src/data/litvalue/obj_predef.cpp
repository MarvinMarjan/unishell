#include "obj_predef.h"


lit::LiteralValue* lit::newFileDataObj(const std::string& fileName, const std::string& fileEx, const int size, const fsys::FileF::FileAtts& atts) noexcept
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


lit::LiteralValue* lit::newRegexResultObj(std::smatch& match)
{
	LiteralValue* list = lit(LitList());

	if (match.size())
	asObj(list).insert({ "full", lit(match[0]) });

	asObj(list).insert({ "group", lit(LitList()) });

	for (size_t i = 1; i < match.size(); i++)
		asList(asObj(list).at("group")).push_back(lit(match[i].str()));

	return list;
}

lit::LiteralValue* lit::newSysMemStatObj(const SystemMemoryInfo& memInfo)
{
	return lit::lit(lit::LitObject({
		{"availableMemory", lit::lit((double)memInfo.availableMemory)},
		{"memoryAvailablePercent", lit::lit((double)memInfo.memoryAvailablePercent)},
		{"totalInstalledMemory", lit::lit((double)memInfo.totalInstalledMemory)}
	}));
}

lit::LiteralValue* lit::newSysDiskStatObj(const SystemDiskInfo& diskInfo)
{
	return lit::lit(lit::LitObject({
		{"totalBytes", lit::lit((double)diskInfo.totalBytes)},
		{"totalBytesAvailable", lit::lit((double)diskInfo.totalBytesAvailable)},
		{"totalFreeBytes", lit::lit((double)diskInfo.totalFreeBytes)}
	}));
}