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
		static inline void write(const std::string& path, std::string data, std::ios_base::openmode mode = std::ios::out) {
			std::ofstream file(path.c_str(), mode);

			if (file.fail())
				throw FileException {path};

			file << data;

			file.close();
		}

		static inline std::string readAsString(const std::string& path) {
			return VectorUtil::join(readAsList(path), "\n");
		}

		static inline StringList readAsList(const std::string& path) {
			std::ifstream file(path.c_str());
			StringList content;
			std::string buff;

			if (file.fail())
				throw FileException {path};

			while (std::getline(file, buff))
				content.push_back(buff);

			file.close();
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

		static inline bool exists(const std::string& name) noexcept {
			return fs::exists(name);
		}
	};
}