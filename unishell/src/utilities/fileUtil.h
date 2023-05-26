#pragma once

#include <filesystem>
#include <fstream>

#include "stringUtil.h"

#include "../system/global.h"

#define N_BYTE		1000
#define N_KILO_BYTE	1000000
#define N_MEGA_BYTE 1000000000
#define N_GIGA_BYTE 1000000000000

namespace fs = std::filesystem;

typedef std::vector<fs::directory_entry> FileList;
typedef fs::directory_entry FileEntry;

class FileUtil
{
public:
	static std::string formatFileEntryAsString(const FileEntry& file);
	static std::string formatFileSizeAsString(uintmax_t size);

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