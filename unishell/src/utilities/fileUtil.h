#pragma once

#include <filesystem>
#include <fstream>

#include "stringUtil.h"
#include "opUtil.h"

#include "../system/global.h"

#define N_BYTE		1000.0
#define N_KILO_BYTE	1000000.0
#define N_MEGA_BYTE 1000000000.0
#define N_GIGA_BYTE 1000000000000.0

namespace fs = std::filesystem;

typedef std::vector<fs::directory_entry> FileList;
typedef fs::directory_entry FileEntry;

class FileUtil
{
public:
	struct FormatedFileData {
		BaseColorStructure* cl = nullptr;
		std::string type;
	};

	struct FileAtts
	{
		bool archive;
		bool compressed;
		bool device;
		bool directory;
		bool ea;
		bool encrypted;
		bool hidden;
		bool integrityStream;
		bool normal;
		bool notContentIndexed;
		bool noScrubData;
		bool offline;
		bool pinned;
		bool readOnly;
		bool recallOnDataAccess;
		bool recallOnOpen;
		bool reparsePoint;
		bool sparseFile;
		bool system;
		bool strictlySequential;
		bool temporary;
		bool virt;
	};

	static inline FormatedFileData newFormatedFileData(BaseColorStructure* cl, std::string type) {
		FormatedFileData data;

		data.cl = cl;
		data.type = type;

		return data;
	}

	// file data formating
	static std::string formatFileEntryAsString(const FileEntry& file);
	static std::string formatFileSizeAsString(uintmax_t size);

	static FileAtts getFileAtts(const FileEntry& file);

	static inline FormatedFileData getFFDByFileAttribute(FileAtts att) {
		FormatedFileData data;

		if (att.directory)		data = newFormatedFileData(__clr_fs_file_type_dir, "dir");
		if (att.archive)		data = newFormatedFileData(__clr_fs_file_type_archive, "archive");
		if (att.hidden)			data = newFormatedFileData(__clr_fs_file_type_hidden, "hidden");
		if (att.reparsePoint)	data = newFormatedFileData(__clr_fs_file_type_symlink, "symlink");
		if (att.temporary)		data = newFormatedFileData(__clr_fs_file_type_temporary, "temporary");
		if (att.normal)			data = newFormatedFileData(__clr_fs_file_type_regular, "normal");

		if (!data.cl) data = newFormatedFileData(__clr_fs_file_type_other, "other");

		return data;
	}


	static inline FileList fileList(const std::string& path) {
		FileList list;

		for (const FileEntry& it : fs::directory_iterator(path))
			list.push_back(it);

		return list;
	}

	static inline bool exists(const std::string& name) {
		return fs::exists(name);
	}
};