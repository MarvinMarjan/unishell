#include "fileUtil.h"

#include "typeUtil.h"
#include "../system/system.h"	

std::string FileUtil::formatFileEntryAsString(const FileEntry& file) {
	std::stringstream str;
	std::string name = file.path().filename().string();

	FormatedFileData data = getFFDByFileAttribute(getFileAtts(file));

	// size
	str << formatFileSizeAsString(file.file_size()) << "    ";

	// type
	str << std::setw(9) << std::left << data.type;

	// name
	str << data.cl->toString();
	str << name << endclr;

	return str.str();
}

std::string FileUtil::formatFileSizeAsString(uintmax_t size) {
	std::stringstream str;
	std::string sizeNotation = "BT";
	BaseColorStructure* cl = __clr_fs_filesize1;
	double dsize = (double)size;

	if (size >= N_BYTE && size < N_KILO_BYTE) {
		dsize = double(size / N_BYTE);
		sizeNotation = "KB";
		cl = __clr_fs_filesize2;
	}

	else if (size >= N_KILO_BYTE && size < N_MEGA_BYTE) {
		dsize = double(size / N_KILO_BYTE);
		sizeNotation = "MB";
		cl = __clr_fs_filesize3;
	}

	else if (size >= N_MEGA_BYTE && size < N_GIGA_BYTE) {
		dsize = double(size / N_MEGA_BYTE);
		sizeNotation = "GB";
		cl = __clr_fs_filesize4;
	}

	str << std::setw(6) << std::left << std::fixed << ((std::round(dsize) == dsize) ? std::setprecision(0) : std::setprecision(1)) << dsize << sizeNotation;

	return cl->toString() + str.str() + endclr;
}


FileUtil::FileAtts FileUtil::getFileAtts(const FileEntry& file) {
	FileAtts atts;
	DWORD att = GetFileAttributes(StringUtil::charToWchar(file.path().string().c_str()));

	atts.archive			= OPUtil::bwAnd(att, FILE_ATTRIBUTE_ARCHIVE);
	atts.compressed			= OPUtil::bwAnd(att, FILE_ATTRIBUTE_COMPRESSED);
	atts.device				= OPUtil::bwAnd(att, FILE_ATTRIBUTE_DEVICE);
	atts.directory			= OPUtil::bwAnd(att, FILE_ATTRIBUTE_DIRECTORY);
	atts.ea					= OPUtil::bwAnd(att, FILE_ATTRIBUTE_EA);
	atts.encrypted			= OPUtil::bwAnd(att, FILE_ATTRIBUTE_ENCRYPTED);
	atts.hidden				= OPUtil::bwAnd(att, FILE_ATTRIBUTE_HIDDEN);
	atts.integrityStream	= OPUtil::bwAnd(att, FILE_ATTRIBUTE_INTEGRITY_STREAM);
	atts.normal				= OPUtil::bwAnd(att, FILE_ATTRIBUTE_NORMAL);
	atts.noScrubData		= OPUtil::bwAnd(att, FILE_ATTRIBUTE_NO_SCRUB_DATA);
	atts.notContentIndexed	= OPUtil::bwAnd(att, FILE_ATTRIBUTE_NOT_CONTENT_INDEXED);
	atts.offline			= OPUtil::bwAnd(att, FILE_ATTRIBUTE_OFFLINE);
	atts.pinned				= OPUtil::bwAnd(att, FILE_ATTRIBUTE_PINNED);
	atts.readOnly			= OPUtil::bwAnd(att, FILE_ATTRIBUTE_READONLY);
	atts.recallOnDataAccess = OPUtil::bwAnd(att, FILE_ATTRIBUTE_RECALL_ON_DATA_ACCESS);
	atts.recallOnOpen		= OPUtil::bwAnd(att, FILE_ATTRIBUTE_RECALL_ON_OPEN);
	atts.reparsePoint		= OPUtil::bwAnd(att, FILE_ATTRIBUTE_REPARSE_POINT);
	atts.sparseFile			= OPUtil::bwAnd(att, FILE_ATTRIBUTE_SPARSE_FILE);
	atts.strictlySequential = OPUtil::bwAnd(att, FILE_ATTRIBUTE_STRICTLY_SEQUENTIAL);
	atts.system				= OPUtil::bwAnd(att, FILE_ATTRIBUTE_SYSTEM);
	atts.temporary			= OPUtil::bwAnd(att, FILE_ATTRIBUTE_TEMPORARY);
	atts.virt				= OPUtil::bwAnd(att, FILE_ATTRIBUTE_ARCHIVE);

	return atts;
}