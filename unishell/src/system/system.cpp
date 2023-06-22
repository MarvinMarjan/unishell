#include "system.h"

bool System::abort = false;

System::System()
{
	addSysId("NAME",	lit::lit("unishell"));
	addSysId("OS",		lit::lit("Windows"));

	__settings->addOption({ "String Color", lit::lit(__clr_quoted->toStrColorStructure()), ValueRepresentsColor });
	__settings->addOption({ "Raw String Color", lit::lit(__clr_raw_string->toStrColorStructure()), ValueRepresentsColor });
	__settings->addOption({ "Escape Character Color", lit::lit(__clr_escape_char->toStrColorStructure()), ValueRepresentsColor });

	__settings->addOption({ "Number Color", lit::lit(__clr_numbers->toStrColorStructure()), ValueRepresentsColor });
	__settings->addOption({ "Operator Color", lit::lit(__clr_operators->toStrColorStructure()), ValueRepresentsColor });
	__settings->addOption({ "Keyword Color", lit::lit(__clr_keyword->toStrColorStructure()), ValueRepresentsColor });
	__settings->addOption({ "Boolean Color", lit::lit(__clr_boolean->toStrColorStructure()), ValueRepresentsColor });

	__settings->addOption({ "Identifier Color", lit::lit(__clr_identifier->toStrColorStructure()), ValueRepresentsColor });
	__settings->addOption({ "Existent Identifier Color", lit::lit(__clr_ex_identifier->toStrColorStructure()), ValueRepresentsColor });
	__settings->addOption({ "System Identifier Color", lit::lit(__clr_sys_identifier->toStrColorStructure()), ValueRepresentsColor });
	__settings->addOption({ "Existent System Identifier Color", lit::lit(__clr_ex_sys_identifier->toStrColorStructure()), ValueRepresentsColor });
	
	__settings->addOption({ "Literal Type Color", lit::lit(__clr_type_literal->toStrColorStructure()), ValueRepresentsColor });
	__settings->addOption({ "Number Type Color", lit::lit(__clr_type_number->toStrColorStructure()), ValueRepresentsColor });
	__settings->addOption({ "Bool Type Color", lit::lit(__clr_type_bool->toStrColorStructure()), ValueRepresentsColor });
	__settings->addOption({ "List Type Color", lit::lit(__clr_type_list->toStrColorStructure()), ValueRepresentsColor });
	__settings->addOption({ "Object Type Color", lit::lit(__clr_type_object->toStrColorStructure()), ValueRepresentsColor });
	__settings->addOption({ "Any Type Color", lit::lit(__clr_type_any->toStrColorStructure()), ValueRepresentsColor });

	__settings->addOption({ "Cursor Color", lit::lit(__clr_cursor->toStrColorStructure()), ValueRepresentsColor });

	__settings->addOption({ "Flag Color", lit::lit(__clr_flag->toStrColorStructure()), ValueRepresentsColor });

	__settings->addOption({ "Command Color", lit::lit(__clr_command->toStrColorStructure()), ValueRepresentsColor });
	__settings->addOption({ "Multi Command Color", lit::lit(__clr_multi_command->toStrColorStructure()), ValueRepresentsColor });

	__settings->addOption({ "Type Command Color", lit::lit(__clr_type_command->toStrColorStructure()), ValueRepresentsColor });
	__settings->addOption({ "Literal Command Color", lit::lit(__clr_literal_command->toStrColorStructure()), ValueRepresentsColor });
	__settings->addOption({ "Number Command Color", lit::lit(__clr_number_command->toStrColorStructure()), ValueRepresentsColor });
	__settings->addOption({ "List Command Color", lit::lit(__clr_list_command->toStrColorStructure()), ValueRepresentsColor });
	__settings->addOption({ "Object Command Color", lit::lit(__clr_object_command->toStrColorStructure()), ValueRepresentsColor });
	__settings->addOption({ "System Command Color", lit::lit(__clr_system_command->toStrColorStructure()), ValueRepresentsColor });
	__settings->addOption({ "Filesystem Command Color", lit::lit(__clr_filesystem_command->toStrColorStructure()), ValueRepresentsColor });
	__settings->addOption({ "Regex Command Color", lit::lit(__clr_regex_command->toStrColorStructure()), ValueRepresentsColor });

	__settings->addOption({ "Enclose Scope 1 Color", lit::lit(__clr_encloses_s1->toStrColorStructure()), ValueRepresentsColor });
	__settings->addOption({ "Enclose Scope 2 Color", lit::lit(__clr_encloses_s2->toStrColorStructure()), ValueRepresentsColor });
	__settings->addOption({ "Enclose Scope 3 Color", lit::lit(__clr_encloses_s3->toStrColorStructure()), ValueRepresentsColor });
	__settings->addOption({ "Enclose Scope 4 Color", lit::lit(__clr_encloses_s4->toStrColorStructure()), ValueRepresentsColor });

	__settings->addOption({ "Regular File Type Color", lit::lit(__clr_fs_file_type_regular->toStrColorStructure()), ValueRepresentsColor });
	__settings->addOption({ "Symlink File Type Color", lit::lit(__clr_fs_file_type_symlink->toStrColorStructure()), ValueRepresentsColor });
	__settings->addOption({ "Dir File Type Color", lit::lit(__clr_fs_file_type_dir->toStrColorStructure()), ValueRepresentsColor });
	__settings->addOption({ "Hidden File Type Color", lit::lit(__clr_fs_file_type_hidden->toStrColorStructure()), ValueRepresentsColor });
	__settings->addOption({ "Archive File Type Color", lit::lit(__clr_fs_file_type_archive->toStrColorStructure()), ValueRepresentsColor });
	__settings->addOption({ "Temporary File Type Color", lit::lit(__clr_fs_file_type_temporary->toStrColorStructure()), ValueRepresentsColor });
	__settings->addOption({ "Other File Type Color", lit::lit(__clr_fs_file_type_other->toStrColorStructure()), ValueRepresentsColor });

	__settings->addOption({ "File Size 1 Color", lit::lit(__clr_fs_filesize1->toStrColorStructure()), ValueRepresentsColor });
	__settings->addOption({ "File Size 2 Color", lit::lit(__clr_fs_filesize2->toStrColorStructure()), ValueRepresentsColor });
	__settings->addOption({ "File Size 3 Color", lit::lit(__clr_fs_filesize3->toStrColorStructure()), ValueRepresentsColor });
	__settings->addOption({ "File Size 4 Color", lit::lit(__clr_fs_filesize4->toStrColorStructure()), ValueRepresentsColor });

	__settings->addOption({ "Text File Extension Color", lit::lit(__clr_fs_file_extension_text->toStrColorStructure()), ValueRepresentsColor });
	__settings->addOption({ "Image File Extension Color", lit::lit(__clr_fs_file_extension_image->toStrColorStructure()), ValueRepresentsColor });
	__settings->addOption({ "Video File Extension Color", lit::lit(__clr_fs_file_extension_video->toStrColorStructure()), ValueRepresentsColor });
	__settings->addOption({ "Audio File Extension Color", lit::lit(__clr_fs_file_extension_audio->toStrColorStructure()), ValueRepresentsColor });
	__settings->addOption({ "Binary File Extension Color", lit::lit(__clr_fs_file_extension_binary->toStrColorStructure()), ValueRepresentsColor });
	__settings->addOption({ "Other File Extension Color", lit::lit(__clr_fs_file_extension_other->toStrColorStructure()), ValueRepresentsColor });

	__settings->addOption({ "Param Name Color", lit::lit(__clr_help_param_name->toStrColorStructure()), ValueRepresentsColor });
	__settings->addOption({ "Flag Meaning Color", lit::lit(__clr_help_flag_meaning->toStrColorStructure()), ValueRepresentsColor });
	__settings->addOption({ "Optional Color", lit::lit(__clr_help_optional->toStrColorStructure()), ValueRepresentsColor });
	__settings->addOption({ "Undefined Param Size Color", lit::lit(__clr_help_undefined_param_size->toStrColorStructure()), ValueRepresentsColor });
}


Identifier* System::getEnvId(const std::string& idName, const int index)
{
	Identifier* identifier = __environment->getId(idName);

	if (!identifier)
		throw SystemException(EnvironmentError, "Unknown indentifier: " + idformat(idName),
			(index != -1) ? ExceptionRef(*__userInput, index) : ExceptionRef(""));

	return identifier;
}


void System::delEnvId(const std::string& idName)
{
	if (__environment->exists(idName) && !__environment->isSysId(idName))
		__environment->delId(idName);
	else if (!__environment->isSysId(idName))
		throw SystemException(EnvironmentError, "Unknown identifier: " + idformat(idName));
	else
		throw SystemException(EnvironmentError, "Can't delete system identifiers.");
}