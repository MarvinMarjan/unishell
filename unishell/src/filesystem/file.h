#pragma once

#include <filesystem>
#include <fstream>

#include "../utilities/vectorUtil.h"
#include "../utilities/opUtil.h"

#include "../system/global.h"

namespace fs = std::filesystem;

typedef std::vector<fs::directory_entry> FileList;
typedef fs::directory_entry FileEntry;

namespace fsys
{
	class FileException 
	{
	public:
		std::string path;
	};

	class File
	{
	public:
		static inline std::string readFileAsString(const std::string& path) {
			StringList content = readFileAsList(path);

			return VectorUtil::join(content, "\n");
		}

		static inline StringList readFileAsList(const std::string& path) {
			std::ifstream file(path.c_str());
			StringList content;
			std::string buff;

			if (file.fail())
				throw FileException {path};

			while (std::getline(file, buff))
				content.push_back(buff);

			return content;
		}

		static inline FileList fileList(const std::string& path) {
			FileList list;

			for (const FileEntry& it : fs::directory_iterator(path))
				list.push_back(it);

			return list;
		}

		static inline uintmax_t fileSize(const std::string& path) {
			return fs::file_size(path);
		}

		static LiteralValue* getFileDataObjFromFile(const std::string& path);

		static inline bool exists(const std::string& name) {
			return fs::exists(name);
		}
	};
}