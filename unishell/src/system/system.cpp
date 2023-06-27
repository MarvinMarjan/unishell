#include "system.h"

#include "settings/option_callback_def.h"

bool System::abort = false;

System::System()
{
	addSysId("NAME",	lit::lit("unishell"));
	addSysId("OS",		lit::lit("Windows"));


	__settings->addSection(Section({
		{"Autocomplete Suggestion Color", lit::lit(__clr_autocomplete_suggestion->toStrColorStructure()), onValueChange_BaseColorStructure(__clr_autocomplete_suggestion), {lit::LitType::Literal}, ValueRepresentsColor}
	}));

	__settings->addSection(Section({
		{ "String Color",			lit::lit(__clr_quoted->toStrColorStructure()), onValueChange_BaseColorStructure(__clr_quoted), {lit::LitType::Literal}, ValueRepresentsColor},
		{ "Raw String Color",		lit::lit(__clr_raw_string->toStrColorStructure()), onValueChange_BaseColorStructure(__clr_raw_string), {lit::LitType::Literal}, ValueRepresentsColor },
		{ "Escape Character Color", lit::lit(__clr_escape_char->toStrColorStructure()), onValueChange_BaseColorStructure(__clr_escape_char), {lit::LitType::Literal}, ValueRepresentsColor}
		}));

	__settings->addSection(Section({
		{ "Number Color",	lit::lit(__clr_numbers->toStrColorStructure()), onValueChange_BaseColorStructure(__clr_numbers), {lit::LitType::Literal}, ValueRepresentsColor},
		{ "Operator Color", lit::lit(__clr_operators->toStrColorStructure()), onValueChange_BaseColorStructure(__clr_operators), {lit::LitType::Literal}, ValueRepresentsColor},
		{ "Keyword Color",	lit::lit(__clr_keyword->toStrColorStructure()), onValueChange_BaseColorStructure(__clr_keyword), {lit::LitType::Literal}, ValueRepresentsColor},
		{ "Boolean Color",	lit::lit(__clr_boolean->toStrColorStructure()), onValueChange_BaseColorStructure(__clr_boolean), {lit::LitType::Literal}, ValueRepresentsColor}
		}));
	
	__settings->addSection(Section({
		{ "Identifier Color",					lit::lit(__clr_identifier->toStrColorStructure()), onValueChange_BaseColorStructure(__clr_identifier), {lit::LitType::Literal}, ValueRepresentsColor},
		{ "Existent Identifier Color",			lit::lit(__clr_ex_identifier->toStrColorStructure()), onValueChange_BaseColorStructure(__clr_ex_identifier), {lit::LitType::Literal}, ValueRepresentsColor },
		{ "System Identifier Color",			lit::lit(__clr_sys_identifier->toStrColorStructure()), onValueChange_BaseColorStructure(__clr_sys_identifier), {lit::LitType::Literal}, ValueRepresentsColor },
		{ "Existent System Identifier Color",	lit::lit(__clr_ex_sys_identifier->toStrColorStructure()), onValueChange_BaseColorStructure(__clr_ex_sys_identifier), {lit::LitType::Literal}, ValueRepresentsColor }
		}));

	__settings->addSection(Section({
		{ "Literal Type Color", lit::lit(__clr_type_literal->toStrColorStructure()), onValueChange_BaseColorStructure(__clr_type_literal), {lit::LitType::Literal}, ValueRepresentsColor },
		{ "Number Type Color",	lit::lit(__clr_type_number->toStrColorStructure()), onValueChange_BaseColorStructure(__clr_type_number), {lit::LitType::Literal}, ValueRepresentsColor },
		{ "Bool Type Color",	lit::lit(__clr_type_bool->toStrColorStructure()), onValueChange_BaseColorStructure(__clr_type_bool), {lit::LitType::Literal}, ValueRepresentsColor },
		{ "List Type Color",	lit::lit(__clr_type_list->toStrColorStructure()), onValueChange_BaseColorStructure(__clr_type_list), {lit::LitType::Literal}, ValueRepresentsColor },
		{ "Object Type Color",	lit::lit(__clr_type_object->toStrColorStructure()), onValueChange_BaseColorStructure(__clr_type_object), {lit::LitType::Literal}, ValueRepresentsColor },
		{ "Any Type Color",		lit::lit(__clr_type_any->toStrColorStructure()), onValueChange_BaseColorStructure(__clr_type_any), {lit::LitType::Literal}, ValueRepresentsColor }
		}));

	__settings->addSection(Section({
		{ "Cursor Color", lit::lit(__clr_cursor->toStrColorStructure()), onValueChange_BaseColorStructure(__clr_cursor), {lit::LitType::Literal}, ValueRepresentsColor }
		}));

	__settings->addSection(Section({
		{ "Flag Color", lit::lit(__clr_flag->toStrColorStructure()), onValueChange_BaseColorStructure(__clr_flag), {lit::LitType::Literal}, ValueRepresentsColor }
		}));

	__settings->addSection(Section({
		{ "Command Color",			lit::lit(__clr_command->toStrColorStructure()), onValueChange_BaseColorStructure(__clr_command), {lit::LitType::Literal}, ValueRepresentsColor },
		{ "Multi Command Color",	lit::lit(__clr_multi_command->toStrColorStructure()), onValueChange_BaseColorStructure(__clr_multi_command), {lit::LitType::Literal}, ValueRepresentsColor }
		}));

	__settings->addSection(Section({
		{ "Type Command Color",			lit::lit(__clr_type_command->toStrColorStructure()), onValueChange_BaseColorStructure(__clr_type_command), {lit::LitType::Literal}, ValueRepresentsColor },
		{ "Literal Command Color",		lit::lit(__clr_literal_command->toStrColorStructure()), onValueChange_BaseColorStructure(__clr_literal_command), {lit::LitType::Literal}, ValueRepresentsColor },
		{ "Number Command Color",		lit::lit(__clr_number_command->toStrColorStructure()), onValueChange_BaseColorStructure(__clr_number_command), {lit::LitType::Literal}, ValueRepresentsColor },
		{ "List Command Color",			lit::lit(__clr_list_command->toStrColorStructure()), onValueChange_BaseColorStructure(__clr_list_command), {lit::LitType::Literal}, ValueRepresentsColor },
		{ "Object Command Color",		lit::lit(__clr_object_command->toStrColorStructure()), onValueChange_BaseColorStructure(__clr_object_command), {lit::LitType::Literal}, ValueRepresentsColor },
		{ "System Command Color",		lit::lit(__clr_system_command->toStrColorStructure()), onValueChange_BaseColorStructure(__clr_system_command), {lit::LitType::Literal}, ValueRepresentsColor },
		{ "Filesystem Command Color",	lit::lit(__clr_filesystem_command->toStrColorStructure()), onValueChange_BaseColorStructure(__clr_filesystem_command), {lit::LitType::Literal}, ValueRepresentsColor },
		{ "Regex Command Color",		lit::lit(__clr_regex_command->toStrColorStructure()), onValueChange_BaseColorStructure(__clr_regex_command), {lit::LitType::Literal}, ValueRepresentsColor }
		}));

	__settings->addSection(Section({
		{ "Enclose Scope 1 Color", lit::lit(__clr_encloses_s1->toStrColorStructure()), onValueChange_BaseColorStructure(__clr_encloses_s1), {lit::LitType::Literal}, ValueRepresentsColor },
		{ "Enclose Scope 2 Color", lit::lit(__clr_encloses_s2->toStrColorStructure()), onValueChange_BaseColorStructure(__clr_encloses_s2), {lit::LitType::Literal}, ValueRepresentsColor },
		{ "Enclose Scope 3 Color", lit::lit(__clr_encloses_s3->toStrColorStructure()), onValueChange_BaseColorStructure(__clr_encloses_s3), {lit::LitType::Literal}, ValueRepresentsColor },
		{ "Enclose Scope 4 Color", lit::lit(__clr_encloses_s4->toStrColorStructure()), onValueChange_BaseColorStructure(__clr_encloses_s4), {lit::LitType::Literal}, ValueRepresentsColor }
		}));

	__settings->addSection(Section({
		{ "Regular File Type Color",	lit::lit(__clr_fs_file_type_regular->toStrColorStructure()), onValueChange_BaseColorStructure(__clr_fs_file_type_regular), {lit::LitType::Literal}, ValueRepresentsColor },
		{ "Symlink File Type Color",	lit::lit(__clr_fs_file_type_symlink->toStrColorStructure()), onValueChange_BaseColorStructure(__clr_fs_file_type_symlink), {lit::LitType::Literal}, ValueRepresentsColor },
		{ "Dir File Type Color",		lit::lit(__clr_fs_file_type_dir->toStrColorStructure()), onValueChange_BaseColorStructure(__clr_fs_file_type_dir), {lit::LitType::Literal}, ValueRepresentsColor },
		{ "Hidden File Type Color",		lit::lit(__clr_fs_file_type_hidden->toStrColorStructure()), onValueChange_BaseColorStructure(__clr_fs_file_type_hidden), {lit::LitType::Literal}, ValueRepresentsColor },
		{ "Archive File Type Color",	lit::lit(__clr_fs_file_type_archive->toStrColorStructure()), onValueChange_BaseColorStructure(__clr_fs_file_type_archive), {lit::LitType::Literal}, ValueRepresentsColor },
		{ "Temporary File Type Color",	lit::lit(__clr_fs_file_type_temporary->toStrColorStructure()), onValueChange_BaseColorStructure(__clr_fs_file_type_temporary), {lit::LitType::Literal}, ValueRepresentsColor },
		{ "Other File Type Color",		lit::lit(__clr_fs_file_type_other->toStrColorStructure()), onValueChange_BaseColorStructure(__clr_fs_file_type_other), {lit::LitType::Literal}, ValueRepresentsColor }
		}));

	__settings->addSection(Section({
		{ "File Size 1 Color", lit::lit(__clr_fs_filesize1->toStrColorStructure()), onValueChange_BaseColorStructure(__clr_fs_filesize1), {lit::LitType::Literal}, ValueRepresentsColor },
		{ "File Size 2 Color", lit::lit(__clr_fs_filesize2->toStrColorStructure()), onValueChange_BaseColorStructure(__clr_fs_filesize2), {lit::LitType::Literal}, ValueRepresentsColor },
		{ "File Size 3 Color", lit::lit(__clr_fs_filesize3->toStrColorStructure()), onValueChange_BaseColorStructure(__clr_fs_filesize3), {lit::LitType::Literal}, ValueRepresentsColor },
		{ "File Size 4 Color", lit::lit(__clr_fs_filesize4->toStrColorStructure()), onValueChange_BaseColorStructure(__clr_fs_filesize4), {lit::LitType::Literal}, ValueRepresentsColor }
		}));

	__settings->addSection(Section({
		{ "Text File Extension Color",		lit::lit(__clr_fs_file_extension_text->toStrColorStructure()), onValueChange_BaseColorStructure(__clr_fs_file_extension_text), {lit::LitType::Literal}, ValueRepresentsColor },
		{ "Image File Extension Color",		lit::lit(__clr_fs_file_extension_image->toStrColorStructure()), onValueChange_BaseColorStructure(__clr_fs_file_extension_image), {lit::LitType::Literal}, ValueRepresentsColor },
		{ "Video File Extension Color",		lit::lit(__clr_fs_file_extension_video->toStrColorStructure()), onValueChange_BaseColorStructure(__clr_fs_file_extension_video), {lit::LitType::Literal}, ValueRepresentsColor },
		{ "Audio File Extension Color",		lit::lit(__clr_fs_file_extension_audio->toStrColorStructure()), onValueChange_BaseColorStructure(__clr_fs_file_extension_audio), {lit::LitType::Literal}, ValueRepresentsColor },
		{ "Binary File Extension Color",	lit::lit(__clr_fs_file_extension_binary->toStrColorStructure()), onValueChange_BaseColorStructure(__clr_fs_file_extension_binary), {lit::LitType::Literal}, ValueRepresentsColor },
		{ "Other File Extension Color",		lit::lit(__clr_fs_file_extension_other->toStrColorStructure()), onValueChange_BaseColorStructure(__clr_fs_file_extension_other), {lit::LitType::Literal}, ValueRepresentsColor }
		}));

	__settings->addSection(Section({
		{ "Param Name Color",			lit::lit(__clr_help_param_name->toStrColorStructure()), onValueChange_BaseColorStructure(__clr_help_param_name), {lit::LitType::Literal}, ValueRepresentsColor },
		{ "Flag Meaning Color",			lit::lit(__clr_help_flag_meaning->toStrColorStructure()), onValueChange_BaseColorStructure(__clr_help_flag_meaning), {lit::LitType::Literal}, ValueRepresentsColor },
		{ "Optional Color",				lit::lit(__clr_help_optional->toStrColorStructure()), onValueChange_BaseColorStructure(__clr_help_optional), {lit::LitType::Literal}, ValueRepresentsColor },
		{ "Undefined Param Size Color", lit::lit(__clr_help_undefined_param_size->toStrColorStructure()), onValueChange_BaseColorStructure(__clr_help_undefined_param_size), {lit::LitType::Literal}, ValueRepresentsColor }
	}));


	__settings->updateOptionsFromData();
}


Identifier* System::getEnvId(const std::string& idName, const int index)
{
	Identifier* identifier = __environment->getId(idName);

	if (!identifier)
		throw new EnvironmentErr("Unknown indentifier: " + idformat(idName),
			(index != -1) ? ExceptionRef(*__userInput, index) : ExceptionRef(""));

	return identifier;
}


void System::delEnvId(const std::string& idName)
{
	if (__environment->exists(idName) && !__environment->isSysId(idName))
		__environment->delId(idName);
	else if (!__environment->isSysId(idName))
		throw new EnvironmentErr("Unknown identifier: " + idformat(idName));
	else
		throw new EnvironmentErr("Can't delete system identifiers.");
}