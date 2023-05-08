#pragma once

#include "../utilities/stringUtil.h"
#include "pathScanner.h"

#include <algorithm>

class PathHandler
{
public:
	PathHandler(const std::string& path) {
		setPath(path);
	}

	inline void back() noexcept {
		if (dirCount() > 1) {
			path = path.substr(0, StringUtil::findLast(path, '/'));

			if (dirCount() == 1)
				path += '/';
		}
	}

	inline std::string getPath() const noexcept {
		return path;
	}

	inline void setPath(const std::string& path) noexcept {
		if (isDirSeparator(path.back())) this->path = StringUtil::eraseLast(path);
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
};