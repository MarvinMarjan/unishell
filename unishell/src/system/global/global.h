#pragma once

#include "../../color/structure/color_structure.h"
#include "typedecl.h"

#include <map>

class CommandBase;
class RetCommandBase;

class Environment;
class PathHandler;
class Settings;


struct SysStat;


using FSExtension = std::map<StringList, std::string>;

// global variables

extern SysStat*	__sys_stat;

extern Environment*		__environment;
extern PathHandler*		__workingPath;
extern std::string*		__userInput;
extern StringList		__fread_input;
extern Settings*		__settings;


// --> string lists
extern const StringList __keywords;
extern const StringList __boolean;
extern const StringList __colormode;
extern const StringList __color;
extern const StringList __color_formats;
// <--

extern const std::vector<CommandBase*> __sys_commands;
extern const std::vector<RetCommandBase*> __sys_ret_commands;


// --> extension types
extern const FSExtension __fs_file_extensions_text;
extern const FSExtension __fs_file_extensions_image;
extern const FSExtension __fs_file_extensions_video;
extern const FSExtension __fs_file_extensions_audio;
extern const FSExtension __fs_file_extensions_binary;
// <--


extern const std::string __word_separator;



extern const std::string __regex_color_escape_char_pattern;

extern const std::string __regex_id_color_escape_char_pattern;
extern const std::string __regex_rgb_color_escape_char_pattern;
extern const std::string __regex_clr_color_escape_char_pattern;


// --> global color variables
extern BaseColorStructure* __clr_path_color;
extern BaseColorStructure* __clr_path_dollar_sign_color;

extern BaseColorStructure* __clr_autocomplete_suggestion;

extern BaseColorStructure* __clr_quoted;
extern BaseColorStructure* __clr_raw_string;
extern BaseColorStructure* __clr_escape_char;

extern BaseColorStructure* __clr_numbers;
extern BaseColorStructure* __clr_operators;
extern BaseColorStructure* __clr_keyword;
extern BaseColorStructure* __clr_boolean;

extern BaseColorStructure* __clr_identifier;
extern BaseColorStructure* __clr_ex_identifier;
extern BaseColorStructure* __clr_sys_identifier;
extern BaseColorStructure* __clr_ex_sys_identifier;

extern BaseColorStructure* __clr_type_literal;
extern BaseColorStructure* __clr_type_number;
extern BaseColorStructure* __clr_type_bool;
extern BaseColorStructure* __clr_type_list;
extern BaseColorStructure* __clr_type_object;
extern BaseColorStructure* __clr_type_block;
extern BaseColorStructure* __clr_type_any;

extern BaseColorStructure* __clr_cursor;

extern BaseColorStructure* __clr_flag;

extern BaseColorStructure* __clr_command;
extern BaseColorStructure* __clr_multi_command;

extern BaseColorStructure* __clr_type_command;
extern BaseColorStructure* __clr_literal_command;
extern BaseColorStructure* __clr_number_command;
extern BaseColorStructure* __clr_list_command;
extern BaseColorStructure* __clr_object_command;
extern BaseColorStructure* __clr_system_command;
extern BaseColorStructure* __clr_filesystem_command;
extern BaseColorStructure* __clr_regex_command;
extern BaseColorStructure* __clr_json_command;

extern BaseColorStructure* __clr_encloses_s1;
extern BaseColorStructure* __clr_encloses_s2;
extern BaseColorStructure* __clr_encloses_s3;
extern BaseColorStructure* __clr_encloses_s4;


extern BaseColorStructure* __clr_fs_file_type_regular;
extern BaseColorStructure* __clr_fs_file_type_symlink;
extern BaseColorStructure* __clr_fs_file_type_dir;
extern BaseColorStructure* __clr_fs_file_type_hidden;
extern BaseColorStructure* __clr_fs_file_type_archive;
extern BaseColorStructure* __clr_fs_file_type_temporary;
extern BaseColorStructure* __clr_fs_file_type_other;

extern BaseColorStructure* __clr_fs_filesize1;
extern BaseColorStructure* __clr_fs_filesize2;
extern BaseColorStructure* __clr_fs_filesize3;
extern BaseColorStructure* __clr_fs_filesize4;

extern BaseColorStructure* __clr_fs_file_extension_text;
extern BaseColorStructure* __clr_fs_file_extension_image;
extern BaseColorStructure* __clr_fs_file_extension_video;
extern BaseColorStructure* __clr_fs_file_extension_audio;
extern BaseColorStructure* __clr_fs_file_extension_binary;
extern BaseColorStructure* __clr_fs_file_extension_other;

extern BaseColorStructure* __clr_help_param_name;
extern BaseColorStructure* __clr_help_flag_meaning;
extern BaseColorStructure* __clr_help_optional;
extern BaseColorStructure* __clr_help_undefined_param_size;

extern BaseColorStructure* __clr_exception_title;
extern BaseColorStructure* __clr_exception_error;
// <--



// --> Application settings

extern bool __config_input_code_highlight;
extern bool __config_coloring;

// <--
