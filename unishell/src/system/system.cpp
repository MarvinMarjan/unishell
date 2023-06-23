#include "system.h"

bool System::abort = false;

System::System()
{
	addSysId("NAME",	lit::lit("unishell"));
	addSysId("OS",		lit::lit("Windows"));


	__settings->addSection(Section({
		{ "String Color",			lit::lit(__clr_quoted->toStrColorStructure()), ValueRepresentsColor },
		{ "Raw String Color",		lit::lit(__clr_raw_string->toStrColorStructure()), ValueRepresentsColor },
		{ "Escape Character Color", lit::lit(__clr_escape_char->toStrColorStructure()), ValueRepresentsColor }
	}));

	__settings->addSection(Section({
		{ "Number Color",	lit::lit(__clr_numbers->toStrColorStructure()), ValueRepresentsColor },
		{ "Operator Color", lit::lit(__clr_operators->toStrColorStructure()), ValueRepresentsColor },
		{ "Keyword Color",	lit::lit(__clr_keyword->toStrColorStructure()), ValueRepresentsColor },
		{ "Boolean Color",	lit::lit(__clr_boolean->toStrColorStructure()), ValueRepresentsColor }
	}));

	__settings->addSection(Section({
		{ "Identifier Color",					lit::lit(__clr_identifier->toStrColorStructure()), ValueRepresentsColor },
		{ "Existent Identifier Color",			lit::lit(__clr_ex_identifier->toStrColorStructure()), ValueRepresentsColor },
		{ "System Identifier Color",			lit::lit(__clr_sys_identifier->toStrColorStructure()), ValueRepresentsColor },
		{ "Existent System Identifier Color",	lit::lit(__clr_ex_sys_identifier->toStrColorStructure()), ValueRepresentsColor }
	}));

	__settings->addSection(Section({
		{ "Literal Type Color", lit::lit(__clr_type_literal->toStrColorStructure()), ValueRepresentsColor },
		{ "Number Type Color",	lit::lit(__clr_type_number->toStrColorStructure()), ValueRepresentsColor },
		{ "Bool Type Color",	lit::lit(__clr_type_bool->toStrColorStructure()), ValueRepresentsColor },
		{ "List Type Color",	lit::lit(__clr_type_list->toStrColorStructure()), ValueRepresentsColor },
		{ "Object Type Color",	lit::lit(__clr_type_object->toStrColorStructure()), ValueRepresentsColor },
		{ "Any Type Color",		lit::lit(__clr_type_any->toStrColorStructure()), ValueRepresentsColor }
	}));

	__settings->addSection(Section({ 
		{ "Cursor Color", lit::lit(__clr_cursor->toStrColorStructure()), ValueRepresentsColor }
	}));

	__settings->addSection(Section({
		{ "Flag Color", lit::lit(__clr_flag->toStrColorStructure()), ValueRepresentsColor }
	}));

	__settings->addSection(Section({ 
		{ "Command Color",			lit::lit(__clr_command->toStrColorStructure()), ValueRepresentsColor },
		{ "Multi Command Color",	lit::lit(__clr_multi_command->toStrColorStructure()), ValueRepresentsColor }
	}));

	__settings->addSection(Section({
		{ "Type Command Color",			lit::lit(__clr_type_command->toStrColorStructure()), ValueRepresentsColor },
		{ "Literal Command Color",		lit::lit(__clr_literal_command->toStrColorStructure()), ValueRepresentsColor },
		{ "Number Command Color",		lit::lit(__clr_number_command->toStrColorStructure()), ValueRepresentsColor },
		{ "List Command Color",			lit::lit(__clr_list_command->toStrColorStructure()), ValueRepresentsColor },
		{ "Object Command Color",		lit::lit(__clr_object_command->toStrColorStructure()), ValueRepresentsColor },
		{ "System Command Color",		lit::lit(__clr_system_command->toStrColorStructure()), ValueRepresentsColor },
		{ "Filesystem Command Color",	lit::lit(__clr_filesystem_command->toStrColorStructure()), ValueRepresentsColor },
		{ "Regex Command Color",		lit::lit(__clr_regex_command->toStrColorStructure()), ValueRepresentsColor }
	}));

	__settings->addSection(Section({ 
		{ "Enclose Scope 1 Color", lit::lit(__clr_encloses_s1->toStrColorStructure()), ValueRepresentsColor },
		{ "Enclose Scope 2 Color", lit::lit(__clr_encloses_s2->toStrColorStructure()), ValueRepresentsColor },
		{ "Enclose Scope 3 Color", lit::lit(__clr_encloses_s3->toStrColorStructure()), ValueRepresentsColor },
		{ "Enclose Scope 4 Color", lit::lit(__clr_encloses_s4->toStrColorStructure()), ValueRepresentsColor }
	}));

	__settings->addSection(Section({
		{ "Regular File Type Color",	lit::lit(__clr_fs_file_type_regular->toStrColorStructure()), ValueRepresentsColor },
		{ "Symlink File Type Color",	lit::lit(__clr_fs_file_type_symlink->toStrColorStructure()), ValueRepresentsColor },
		{ "Dir File Type Color",		lit::lit(__clr_fs_file_type_dir->toStrColorStructure()), ValueRepresentsColor },
		{ "Hidden File Type Color",		lit::lit(__clr_fs_file_type_hidden->toStrColorStructure()), ValueRepresentsColor },
		{ "Archive File Type Color",	lit::lit(__clr_fs_file_type_archive->toStrColorStructure()), ValueRepresentsColor },
		{ "Temporary File Type Color",	lit::lit(__clr_fs_file_type_temporary->toStrColorStructure()), ValueRepresentsColor },
		{ "Other File Type Color",		lit::lit(__clr_fs_file_type_other->toStrColorStructure()), ValueRepresentsColor }
	}));

	__settings->addSection(Section({
		{ "File Size 1 Color", lit::lit(__clr_fs_filesize1->toStrColorStructure()), ValueRepresentsColor },
		{ "File Size 2 Color", lit::lit(__clr_fs_filesize2->toStrColorStructure()), ValueRepresentsColor },
		{ "File Size 3 Color", lit::lit(__clr_fs_filesize3->toStrColorStructure()), ValueRepresentsColor },
		{ "File Size 4 Color", lit::lit(__clr_fs_filesize4->toStrColorStructure()), ValueRepresentsColor }
	}));

	__settings->addSection(Section({
		{ "Text File Extension Color",		lit::lit(__clr_fs_file_extension_text->toStrColorStructure()), ValueRepresentsColor },
		{ "Image File Extension Color",		lit::lit(__clr_fs_file_extension_image->toStrColorStructure()), ValueRepresentsColor },
		{ "Video File Extension Color",		lit::lit(__clr_fs_file_extension_video->toStrColorStructure()), ValueRepresentsColor },
		{ "Audio File Extension Color",		lit::lit(__clr_fs_file_extension_audio->toStrColorStructure()), ValueRepresentsColor },
		{ "Binary File Extension Color",	lit::lit(__clr_fs_file_extension_binary->toStrColorStructure()), ValueRepresentsColor },
		{ "Other File Extension Color",		lit::lit(__clr_fs_file_extension_other->toStrColorStructure()), ValueRepresentsColor }
	}));

	__settings->addSection(Section({
		{ "Param Name Color",			lit::lit(__clr_help_param_name->toStrColorStructure()), ValueRepresentsColor },
		{ "Flag Meaning Color",			lit::lit(__clr_help_flag_meaning->toStrColorStructure()), ValueRepresentsColor },
		{ "Optional Color",				lit::lit(__clr_help_optional->toStrColorStructure()), ValueRepresentsColor },
		{ "Undefined Param Size Color", lit::lit(__clr_help_undefined_param_size->toStrColorStructure()), ValueRepresentsColor }
	}));
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