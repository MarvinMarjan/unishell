#pragma once

#include "../utilities/stringUtil.h"
#include "../utilities/fileUtil.h"

#include "pathScanner.h"

#include <algorithm>

class PathHandler
{
public:
	PathHandler(const std::string& path);

	void manip(TokenList instructions);


	// returns false if dirName doesn't exists
	inline bool into(const std::string& dirName, bool root = false) {
		if (!root && !FileUtil::exists(path + '/' + dirName)) return false;
		if (root && !FileUtil::exists(dirName)) return false;

		if (root) setPath(dirName, true);
		else setPath(path += ((path.back() != '/') ? '/' + dirName : dirName)); // don't add another '/' if path ends with '/'

		return true;
	}

	// back to the previous directory
	inline void back() noexcept {
		if (dirCount() <= 1) return;

		path = path.substr(0, StringUtil::findLast(path, '/'));

		if (dirCount() == 1)
			path += '/';
	}

	inline std::string getPath() const noexcept {
		return path;
	}

	inline void setPath(const std::string& path, bool ignoreLast = false) noexcept {
		if (isDirSeparator(path.back()) && !ignoreLast) this->path = StringUtil::eraseLast(path);
		else this->path = path;

		std::replace(this->path.begin(), this->path.end(), '\\', '/');
	}


	inline size_t dirCount() const noexcept {
		return StringUtil::split(path, '/').size();
	}

private:
	static constexpr inline bool isDirSeparator(char ch) noexcept {
		return (ch == '/' || ch == '\\');
	}

	std::string path;
	
	bool canManip;
};