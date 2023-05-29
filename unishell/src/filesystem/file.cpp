#include "file.h"

#include "fileFormatting.h"
#include "../utilities/objUtil.h"

LiteralValue* fsys::File::getFileDataObjFromFile(const std::string& path) {
	FileEntry file(path);

	return ObjUtil::newFileDataObj(
		file.path().filename().string(),
		file.path().extension().string(),
		(int)file.file_size(),
		fsys::FileF::getFileAtts(file)
	);
}