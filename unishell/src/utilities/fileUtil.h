#pragma once

#include <filesystem>
#include <fstream>

#include <string>

namespace fs = std::filesystem;

class FileUtil
{
public:
	static inline bool exists(const std::string& name) {
		return fs::exists(name);
	}
};