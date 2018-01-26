# Makefile for customizing C/C++ builds - 138paulmiller 
	
# compiler to use
CC = g++
# directory that contains c/cpp files
SRC_DIR = src
# directory that contains compiled files
OBJ_DIR = obj

#include directory for additional headers
INC_DIR = inc
# directory to hold all compiled c/cpp files
OUT = 3DEngine

#additional flags to use
CPPFLAGS = -std=c++11 -lGL -lGLEW -lSDL2 -lSDL2main

# All objects, creates a list of all potential objects from sources, whether or not compiled yet
# Finds all source files, strips prefix and suffix and renames them as object files
OBJECTS= $(patsubst %, $(OBJ_DIR)/%.o, \
		$(notdir $(basename \
		$(shell find $(SRC_DIR) -type f -name '*.cpp')))) 	

# Objects may not exist yet, so build when needed
.PHONY : clean

Debug: all
	@echo Debug Build Complete

Release : all
	@echo Release Build Complete

Rebuild : clean all
	@echo Rebuild Complete

all: $(OBJECTS)
	$(CC) -o $(OUT) $^ $(CPPFLAGS)

#If obj does not exist(not compiled), compile it into build dir 
$(OBJECTS): $(OBJ_DIR)
	@if [ ! -e "$@" ]; then \
	echo "$(CC) -I$(INC_DIR) $(CPPFLAGS) -c $(shell find $(SRC_DIR) -type f -name $(notdir $(basename $@)).cpp) -o $(OBJ_DIR)/$(notdir $@);"; \
		$(CC) -I$(INC_DIR) $(CPPFLAGS) \
		-c $(shell find $(SRC_DIR) -type f -name $(notdir $(basename $@)).cpp) \
		-o $(OBJ_DIR)/$(notdir $@); \
	fi
		

# Create build directory for objects files
$(OBJ_DIR):
	@mkdir $@

cleanDebug: clean
	@echo Debug


cleanRelease: clean
	@echo Release

#If remove fails, contiue
clean:
	@if [ -e $(OBJ_DIR) ]; then \
	rm -r $(OBJ_DIR); \
	fi; 
	@if [ -e $(OUT) ]; then \
	rm -r $(OUT); \
	fi; 
	@echo Cleaned

	

