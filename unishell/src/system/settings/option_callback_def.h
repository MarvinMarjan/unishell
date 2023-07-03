#pragma once

#include "../../data/litvalue/type.h"
#include "../../color/structure/color_structure.h"
#include "../../color/parser/color_parser.h"
#include "../../instream/scanner/instream_scanner.h"
#include "../memory/memfree.h"


#define onValueChange_BaseColorStructure(clr_pointer) \
	[] (lit::LiteralValue* value) { \
		const TokenList loc_tokens = InstreamScanner(asStr(value), IgnoreCommand).scanTokens(); \
		\
		if (clr_pointer) \
			delete clr_pointer; \
		\
		clr_pointer = ColorParser(loc_tokens, true).parse(); \
		\
		freeTokenListMemory(loc_tokens); \
	}



#define onValueChange_boolean(boolean_val) \
	[] (lit::LiteralValue* value) { \
		boolean_val = asBool(value); \
	}



#define onValueChange_coloring \
	[] (lit::LiteralValue* value) { \
		bool disable = asBool(value); \
		__config_coloring = disable; \
		__config_input_code_highlight = disable; \
		\
		\
		__clr_autocomplete_suggestion->disabled = (!disable); \
		__clr_quoted->disabled = (!disable); \
		__clr_raw_string->disabled = (!disable); \
		__clr_escape_char->disabled = (!disable); \
		__clr_numbers->disabled = (!disable); \
		__clr_operators->disabled = (!disable); \
		__clr_keyword->disabled = (!disable); \
		__clr_boolean->disabled = (!disable); \
		__clr_identifier->disabled = (!disable); \
		__clr_ex_identifier->disabled = (!disable); \
		__clr_sys_identifier->disabled = (!disable); \
		__clr_ex_sys_identifier->disabled = (!disable); \
		__clr_type_literal->disabled = (!disable); \
		__clr_type_number->disabled = (!disable); \
		__clr_type_bool->disabled = (!disable); \
		__clr_type_list->disabled = (!disable); \
		__clr_type_object->disabled = (!disable); \
		__clr_type_block->disabled = (!disable); \
		__clr_type_any->disabled = (!disable); \
		__clr_cursor->disabled = (!disable); \
		__clr_flag->disabled = (!disable); \
		__clr_command->disabled = (!disable); \
		__clr_multi_command->disabled = (!disable); \
		__clr_type_command->disabled = (!disable); \
		__clr_literal_command->disabled = (!disable); \
		__clr_number_command->disabled = (!disable); \
		__clr_list_command->disabled = (!disable); \
		__clr_object_command->disabled = (!disable); \
		__clr_system_command->disabled = (!disable); \
		__clr_filesystem_command->disabled = (!disable); \
		__clr_regex_command->disabled = (!disable); \
		__clr_json_command->disabled = (!disable); \
		__clr_encloses_s1->disabled = (!disable); \
		__clr_encloses_s2->disabled = (!disable); \
		__clr_encloses_s3->disabled = (!disable); \
		__clr_encloses_s4->disabled = (!disable); \
		__clr_fs_file_type_regular->disabled = (!disable); \
		__clr_fs_file_type_symlink->disabled = (!disable); \
		__clr_fs_file_type_dir->disabled = (!disable); \
		__clr_fs_file_type_hidden->disabled = (!disable); \
		__clr_fs_file_type_archive->disabled = (!disable); \
		__clr_fs_file_type_temporary->disabled = (!disable); \
		__clr_fs_file_type_other->disabled = (!disable); \
		__clr_fs_filesize1->disabled = (!disable); \
		__clr_fs_filesize2->disabled = (!disable); \
		__clr_fs_filesize3->disabled = (!disable); \
		__clr_fs_filesize4->disabled = (!disable); \
		__clr_fs_file_extension_text->disabled = (!disable); \
		__clr_fs_file_extension_image->disabled = (!disable); \
		__clr_fs_file_extension_video->disabled = (!disable); \
		__clr_fs_file_extension_audio->disabled = (!disable); \
 		__clr_fs_file_extension_binary->disabled = (!disable); \
		__clr_fs_file_extension_other->disabled = (!disable); \
		__clr_help_param_name->disabled = (!disable); \
		__clr_help_flag_meaning->disabled = (!disable); \
		__clr_help_optional->disabled = (!disable); \
		__clr_help_undefined_param_size->disabled = (!disable); \
		__clr_exception_title->disabled = (!disable); \
		__clr_exception_error->disabled = (!disable); \
	}
