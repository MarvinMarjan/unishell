#pragma once

#include <Windows.h>
#include <cstdint>

#include "../../filesystem/formating/formating.h"

#define GIGABYTE (1024 * 1024 * 1024)
#define MEGABYTE (1024 * 1024)
#define KILOBYTE (1024)


struct SystemMemoryInfo
{
	// bytes
	unsigned long long availableMemory;
	unsigned long long totalInstalledMemory;
	int memoryAvailablePercent;
};

inline MEMORYSTATUSEX getMemoryStatusEx() {
	MEMORYSTATUSEX mem;
	mem.dwLength = sizeof(mem);

	GlobalMemoryStatusEx(&mem);

	return mem;
}

inline SystemMemoryInfo getSystemMemoryInfo() {
	SystemMemoryInfo info;
	MEMORYSTATUSEX memstat = getMemoryStatusEx();

	info.totalInstalledMemory = memstat.ullTotalPhys;
	info.availableMemory = memstat.ullAvailPhys;
	info.memoryAvailablePercent = memstat.dwMemoryLoad;


	return info;
}


struct SystemDiskInfo
{
	long long totalBytesAvailable;
	long long totalBytes;
	long long totalFreeBytes;
};


inline SystemDiskInfo getSystemDiskInfo() {
	SystemDiskInfo info;

	ULARGE_INTEGER btAvailable, totalBt, freeBt;

	GetDiskFreeSpaceExA("C:/", &btAvailable, &totalBt, &freeBt);

	info.totalBytesAvailable = (int64_t)btAvailable.QuadPart;
	info.totalBytes = (int64_t)totalBt.QuadPart;
	info.totalFreeBytes = (int64_t)freeBt.QuadPart;

	return info;
}