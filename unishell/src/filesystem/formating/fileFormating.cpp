#include "fileFormatting.h"

#include "../../data/litvalue/obj_predef.h"
#include "../../algorithm/bit/operations.h"
#include "../../system/system.h"

#include <cmath>

std::string fsys::FileF::formatFileEntryAsString(const FileEntry& file) {
	std::stringstream str;
	const std::string name = file.path().filename().string();
	const bool dir = file.is_directory();

	const FileAtts atts = getFileAtts(file);

	const FormatedFileData ex = formatFileExtensionAsString(file.path().extension().string());
	const FormatedFileData data = getFFDByFileAttribute(atts);


	// using FileEntry::file_size with directories will
	// result in a error (std::filesystem::filesystem_error)
	str << formatFileSizeAsString((dir) ? 0 : file.file_size()) << "   ";

	// raw
	str << std::setw(9) << std::left << data.raw;

	 
	// extension
	str << ex.cl->toString();
	str << std::setw(11) << std::left << ((dir) ? "" : ex.raw);

	// name
	str << data.cl->toString();
	str << name << endclr;

	return str.str();
}

std::string fsys::FileF::formatFileSizeAsString(uintmax_t size) {
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


fsys::FileF::FormatedFileData fsys::FileF::formatFileExtensionAsString(const std::string& ex)
{
	CHECK_GLOBAL_EX(__fs_file_extensions_text, __clr_fs_file_extension_text)
	CHECK_GLOBAL_EX(__fs_file_extensions_image, __clr_fs_file_extension_image)
	CHECK_GLOBAL_EX(__fs_file_extensions_audio, __clr_fs_file_extension_audio)
	CHECK_GLOBAL_EX(__fs_file_extensions_video, __clr_fs_file_extension_video)
	CHECK_GLOBAL_EX(__fs_file_extensions_binary, __clr_fs_file_extension_binary)

	return newFormatedFileData(__clr_fs_file_extension_other, alg::string::toUpper(ex));
}


fsys::FileF::FileAtts fsys::FileF::getFileAtts(const FileEntry& file) {
	FileAtts atts{};
	const DWORD att = GetFileAttributesA(file.path().string().c_str());

	atts.archive =				alg::bit::hasBits(att, FILE_ATTRIBUTE_ARCHIVE);
	atts.compressed =			alg::bit::hasBits(att, FILE_ATTRIBUTE_COMPRESSED);
	atts.device =				alg::bit::hasBits(att, FILE_ATTRIBUTE_DEVICE);
	atts.directory =			alg::bit::hasBits(att, FILE_ATTRIBUTE_DIRECTORY);
	atts.ea =					alg::bit::hasBits(att, FILE_ATTRIBUTE_EA);
	atts.encrypted =			alg::bit::hasBits(att, FILE_ATTRIBUTE_ENCRYPTED);
	atts.hidden =				alg::bit::hasBits(att, FILE_ATTRIBUTE_HIDDEN);
	atts.integrityStream =		alg::bit::hasBits(att, FILE_ATTRIBUTE_INTEGRITY_STREAM);
	atts.normal =				alg::bit::hasBits(att, FILE_ATTRIBUTE_NORMAL);
	atts.noScrubData =			alg::bit::hasBits(att, FILE_ATTRIBUTE_NO_SCRUB_DATA);
	atts.notContentIndexed =	alg::bit::hasBits(att, FILE_ATTRIBUTE_NOT_CONTENT_INDEXED);
	atts.offline =				alg::bit::hasBits(att, FILE_ATTRIBUTE_OFFLINE);
	atts.pinned =				alg::bit::hasBits(att, FILE_ATTRIBUTE_PINNED);
	atts.readOnly =				alg::bit::hasBits(att, FILE_ATTRIBUTE_READONLY);
	atts.recallOnDataAccess =	alg::bit::hasBits(att, FILE_ATTRIBUTE_RECALL_ON_DATA_ACCESS);
	atts.recallOnOpen =			alg::bit::hasBits(att, FILE_ATTRIBUTE_RECALL_ON_OPEN);
	atts.reparsePoint =			alg::bit::hasBits(att, FILE_ATTRIBUTE_REPARSE_POINT);
	atts.sparseFile =			alg::bit::hasBits(att, FILE_ATTRIBUTE_SPARSE_FILE);
	atts.strictlySequential =	alg::bit::hasBits(att, FILE_ATTRIBUTE_STRICTLY_SEQUENTIAL);
	atts.system =				alg::bit::hasBits(att, FILE_ATTRIBUTE_SYSTEM);
	atts.temporary =			alg::bit::hasBits(att, FILE_ATTRIBUTE_TEMPORARY);
	atts.virt =					alg::bit::hasBits(att, FILE_ATTRIBUTE_ARCHIVE);

	return atts;
}