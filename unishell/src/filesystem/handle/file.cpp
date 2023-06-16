#include "file.h"

#include "../formating/fileFormatting.h"
#include "../../data/litvalue/obj_predef.h"

lit::LiteralValue* fsys::File::getFileDataObjFromFile(const std::string& path) {
	const FileEntry file(path);

	return lit::newFileDataObj(
		file.path().filename().string(),
		file.path().extension().string(),
		(int)file.file_size(),
		fsys::FileF::getFileAtts(file)
	);
}