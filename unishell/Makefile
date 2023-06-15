# folders to Make search sources
VPATH := $(shell dir src\* /AD /S)

APP_NAME := uni.exe

BUILD_PATH := build
OBJECT_PATH := $(BUILD_PATH)/obj

CC := g++
CPP_VERSION := -std=c++20
SOURCE := \
	main.cpp \
	src/algorithm/string/manip.cpp \
	src/algorithm/vector/sort.cpp \
	src/color/parser/colorParser.cpp \
	src/commands/definition/helpData.cpp \
	src/commands/definition/filesystemHelpDef.cpp \
	src/commands/definition/listHelpDef.cpp \
	src/commands/definition/literalHelpDef.cpp \
	src/commands/definition/numberTypeDef.cpp \
	src/commands/definition/objectHelpDef.cpp \
	src/commands/definition/regexHelpDef.cpp \
	src/commands/definition/systemHelpDef.cpp \
	src/commands/definition/typeHelpDef.cpp \
	src/filesystem/formating/fileFormating.cpp \
	src/filesystem/handle/file.cpp \
	src/instream/input/instream.cpp \
	src/instream/scanner/instreamScanner.cpp \
	src/parser/processing/token/tokenProcessing.cpp \
	src/path/handler/pathHandler.cpp \
	src/path/scanner/pathScanner.cpp \
	src/system/exception/exceptionRef.cpp \
	src/system/exception/systemException.cpp \
	src/system/global/global.cpp \
	src/system/system.cpp \
	src/utilities/cmdUtil.cpp \
	src/utilities/typeUtil.cpp 



OBJECTS := $(addprefix $(OBJECT_PATH)/, $(notdir $(SOURCE:.cpp=.o)))



# links all objects into a executable file or
# compile the object if it was not found
.PHONY: build
build: $(OBJECT_PATH) $(OBJECTS)
	@ echo Creating $(APP_NAME)
	@ $(CC) $(CPP_VERSION) $(OBJECTS) -o $(APP_NAME)


$(OBJECT_PATH):
	@ echo Creating $(OBJECT_PATH) folder
	@ mkdir "$(OBJECT_PATH)"


# compile source file into object one
$(OBJECT_PATH)/%.o: %.cpp
	@ echo Compiling $(notdir $<)
	@ $(CC) $(CPP_VERSION) -c $< -o $@




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