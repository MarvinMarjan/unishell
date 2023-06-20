#pragma once

#include <Windows.h>
#include <string>

class WindowsSystem
{
public:
	static bool VKIsPressed(const int VK) {
		return ((GetAsyncKeyState(VK) & 0x8000) != 0);
	}

	static void setCursorVisible(const bool visible) {
		CONSOLE_CURSOR_INFO info = { 1, visible };
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	}

	static std::string getEnvVariable(const std::string& varName) {
		char buffer[4096];
		DWORD res = GetEnvironmentVariableA(varName.c_str(), buffer, sizeof(buffer));

		if (res > 0 && res < sizeof(buffer))
			return std::string(buffer);

		return std::string();
	}

	static std::string getSystemDesktopPath() {
		char buff[MAX_PATH];
		
		if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_DESKTOPDIRECTORY, NULL, 0, buff)))
			return std::string(buff);

		return std::string();
	}
};