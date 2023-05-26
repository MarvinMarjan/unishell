#include "fileUtil.h"

std::string FileUtil::formatFileEntryAsString(const FileEntry& file) {
	std::stringstream str;

	std::string name = file.path().filename().string();
	std::string type;

	BaseColorStructure* cl = __clr_fs_file_type_regular;

	if (file.is_symlink()) {
		cl = __clr_fs_file_type_symlink;
		type = "symlink";
	}

	else if (file.is_regular_file()) {
		cl = __clr_fs_file_type_regular;
		type = "file";
	}

	else if (file.is_directory()) {
		cl = __clr_fs_file_type_dir;
		type = "dir";
	}

	else {
		cl = __clr_fs_file_type_other;
		type = "other";
	}


	// size
	str << formatFileSizeAsString(file.file_size()) << "    ";

	// type
	str << std::setw(9) << std::left << type;

	// name
	str << cl->toString();
	str << name << endclr;

	return str.str();
}

std::string FileUtil::formatFileSizeAsString(uintmax_t size) {
	std::stringstream str;
	std::string sizeNotation = "BT";
	BaseColorStructure* cl = __clr_fs_filesize1;

	if (size >= N_BYTE && size < N_KILO_BYTE) {
		size /= N_BYTE;
		sizeNotation = "KB";
		cl = __clr_fs_filesize2;
	}

	else if (size >= N_KILO_BYTE && size < N_MEGA_BYTE) {
		size /= N_KILO_BYTE;
		sizeNotation = "MB";
		cl = __clr_fs_filesize3;
	}

	else if (size >= N_MEGA_BYTE && size < N_GIGA_BYTE) {
		size /= N_MEGA_BYTE;
		sizeNotation = "GB";
		cl = __clr_fs_filesize4;
	}

	str << std::setw(4) << std::left << size << sizeNotation;

	return cl->toString() + str.str() + endclr;
}