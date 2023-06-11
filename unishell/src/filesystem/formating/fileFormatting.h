#pragma once

#include "../handle/file.h"

#define N_BYTE		1000.0
#define N_KILO_BYTE	1000000.0
#define N_MEGA_BYTE 1000000000.0
#define N_GIGA_BYTE 1000000000000.0

// boilerplate
#define CHECK_GLOBAL_EX(src, clr) \
	for (const auto& it : src) { \
		if (VectorUtil::exists(it.first, ex)) \
			return newFormatedFileData(clr, it.second); \
	} \

namespace fsys
{
	class FileF
	{
	public:
		struct FormatedFileData {
			BaseColorStructure* cl = nullptr;
			std::string raw;
		};

		struct FileAtts
		{
			bool archive;
			bool compressed;
			bool device;
			bool directory;
			bool ea;
			bool encrypted;
			bool hidden;
			bool integrityStream;
			bool normal;
			bool notContentIndexed;
			bool noScrubData;
			bool offline;
			bool pinned;
			bool readOnly;
			bool recallOnDataAccess;
			bool recallOnOpen;
			bool reparsePoint;
			bool sparseFile;
			bool system;
			bool strictlySequential;
			bool temporary;
			bool virt;
		};

		static constexpr FormatedFileData newFormatedFileData(BaseColorStructure* cl, const std::string& raw) {
			FormatedFileData data;

			data.cl = cl;
			data.raw = raw;

			return data;
		}

		static std::string formatFileEntryAsString(const FileEntry& file);
		static std::string formatFileSizeAsString(uintmax_t size);

		static FormatedFileData formatFileExtensionAsString(const std::string& ex) {
			CHECK_GLOBAL_EX(__fs_file_extensions_text, __clr_fs_file_extension_text)
			CHECK_GLOBAL_EX(__fs_file_extensions_image, __clr_fs_file_extension_image)
			CHECK_GLOBAL_EX(__fs_file_extensions_audio, __clr_fs_file_extension_audio)
			CHECK_GLOBAL_EX(__fs_file_extensions_video, __clr_fs_file_extension_video)
			CHECK_GLOBAL_EX(__fs_file_extensions_binary, __clr_fs_file_extension_binary)

			return newFormatedFileData(__clr_fs_file_extension_other, StringUtil::toUpper(ex));
		}

		static FileAtts getFileAtts(const FileEntry& file);

		static constexpr FormatedFileData getFFDByFileAttribute(const FileAtts& att) {
			FormatedFileData data;

			if (att.directory)		data = newFormatedFileData(__clr_fs_file_type_dir, "dir");
			if (att.archive)		data = newFormatedFileData(__clr_fs_file_type_archive, "archive");
			if (att.hidden)			data = newFormatedFileData(__clr_fs_file_type_hidden, "hidden");
			if (att.reparsePoint)	data = newFormatedFileData(__clr_fs_file_type_symlink, "symlink");
			if (att.temporary)		data = newFormatedFileData(__clr_fs_file_type_temporary, "temporary");
			if (att.normal)			data = newFormatedFileData(__clr_fs_file_type_regular, "normal");

			if (!data.cl) data = newFormatedFileData(__clr_fs_file_type_other, "other");

			return data;
		}
	};
}