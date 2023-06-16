#pragma once

#include "../../algorithm/vector/item.h"
#include "../../utilities/opUtil.h"
#include "../../system/global/global.h"
#include "../../data/litvalue/type.h"

#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

typedef std::vector<fs::directory_entry> FileList;
typedef fs::directory_entry FileEntry;

namespace fsys
{
	struct FileException {
		std::string path;
	};
	
	class File
	{
	public:
		static void createFile(const std::string& path) {
			std::ofstream file(path.c_str(), std::ios::out);

			if (file.fail())
				throw FileException {path};
		}

		static void removeFile(const std::string& path) {
			if (!exists(path))
				throw FileException {path};

			std::remove(path.c_str());
		}

		static void createDir(const std::string& path) {
			if (!fs::create_directory(path))
				throw FileException {path};
		}

		static void removeDir(const std::string& path, const bool removeAll = false) {
			if (removeAll && fs::remove_all(path)) return;
			else if (fs::remove(path)) return;
			
			throw FileException {path};
		}

		static void write(const std::string& path, const std::string& data, const std::ios_base::openmode mode = std::ios::out) {
			std::ofstream file(path.c_str(), mode);

			if (file.fail())
				throw FileException {path};

			file << data;

			file.close();
		}

		static std::string readAsString(const std::string& path) {
			return alg::vector::join(readAsList(path), "\n");
		}

		static StringList readAsList(const std::string& path) {
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

		static FileList fileList(const std::string& path) {
			FileList list;

			for (const FileEntry& it : fs::directory_iterator(path))
				list.push_back(it);

			return list;
		}

		static StringList fileListAsString(const std::string& path) {
			StringList list;

			for (const FileEntry& it : fs::directory_iterator(path))
				list.push_back(it.path().filename().string());

			return list;
		}

		static uintmax_t fileSize(const std::string& path) {
			return fs::file_size(path);
		}

		static lit::LiteralValue* getFileDataObjFromFile(const std::string& path);

		static bool exists(const std::string& name) noexcept {
			return fs::exists(name);
		}
	};
}