# folders to Make search sources
VPATH := $(shell dir src\* /AD /S)

APP_NAME := uni.exe

BUILD_PATH := build
OBJECT_PATH := $(BUILD_PATH)/obj

CC := g++
CPP_VERSION := -std=c++20
INCLUDE_PATHS := \
	-I deps/json/include

SOURCE := \
	main.cpp \
	src/algorithm/string/manip.cpp \
	src/algorithm/vector/sort.cpp \
	src/color/parser/color_parser.cpp \
	src/color/structure/color_structure.cpp \
	src/commands/definition/filesystem_help.cpp \
	src/commands/definition/list_help.cpp \
	src/commands/definition/literal_help.cpp \
	src/commands/definition/number_type.cpp \
	src/commands/definition/object_help.cpp \
	src/commands/definition/regex_help.cpp \
	src/commands/definition/system_help.cpp \
	src/commands/definition/type_help.cpp \
	src/commands/cmdcore/args.cpp \
	src/commands/cmdcore/cmd.cpp \
	src/commands/cmdcore/help_data.cpp \
	src/filesystem/formating/formating.cpp \
	src/filesystem/handle/file.cpp \
	src/outstream/control/outformat.cpp \
	src/outstrean/color/color_chars.cpp \
	src/instream/input/instream.cpp \
	src/instream/input/render.cpp \
	src/instream/scanner/instream_scanner.cpp \
	src/instream/scanner/search_list.cpp \
	src/environment/identifier/idformat.cpp \
	src/expression/parser/expr_parser.cpp \
	src/expression/interpreter/expr_interpreter.cpp \
	src/parser/processing/token/token_processing.cpp \
	src/path/handler/path_handler.cpp \
	src/path/scanner/path_scanner.cpp \
	src/data/litvalue/litformat.cpp \
	src/data/litvalue/type.cpp \
	src/data/litvalue/obj_predef.cpp \
	src/system/exception/exception_reference.cpp \
	src/system/global/global.cpp \
	src/system/settings/option.cpp \
	src/system/settings/option_format.cpp \
	src/system/system.cpp \



OBJECTS := $(addprefix $(OBJECT_PATH)/, $(notdir $(SOURCE:.cpp=.o)))



# links all objects into a executable file or
# compile the object if it was not found
.PHONY: build
build: $(OBJECT_PATH) $(OBJECTS)
	@ echo Creating $(APP_NAME)
	@ $(CC) $(CPP_VERSION) $(OBJECTS) -o $(BUILD_PATH)/$(APP_NAME)


$(OBJECT_PATH):
	@ echo Creating $(OBJECT_PATH) folder
	@ mkdir "$(OBJECT_PATH)"


# compile source file into object one
$(OBJECT_PATH)/%.o: %.cpp
	@ echo Compiling $(notdir $<)
	@ $(CC) $(CPP_VERSION) $(INCLUDE_PATHS) -c $< -o $@




# rebuild all
.PHONY: rebuild
rebuild:
	@ $(MAKE) -s clean
	@ $(MAKE) -s build




# clear build folder
.PHONY: clean
clean:
	@ echo Removing object files
	@ del /Q "$(OBJECT_PATH)"
	@ rmdir "$(OBJECT_PATH)"