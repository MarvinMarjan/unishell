#pragma once

#include <Windows.h>
#include <string>

class WindowsSystem
{
public:
	static inline void setCursorVisible(bool visible) {
		CONSOLE_CURSOR_INFO info = { 1, visible };
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	}

	static inline std::string getEnvVariable(const std::string& varName) {
		char buffer[4096];
		DWORD res = GetEnvironmentVariableA(varName.c_str(), buffer, sizeof(buffer));

		if (res > 0 && res < sizeof(buffer))
			return std::string(buffer);

		return std::string();
	}

	static inline std::wstring getSystemDesktopPath() {
		PWSTR buff;

		if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_Desktop, 0, NULL, &buff)))
			return buff;

		return std::wstring();
	}
};