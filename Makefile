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

Debug: all
	@echo Debug Build Complete

Release : all
	@echo Release Build Complete


all: $(OBJECTS)
	$(CC) -o $(OUT) $^ $(CPPFLAGS)

#If obj does not exist(not compiled), compile it into build dir 
$(OBJECTS): $(OBJ_DIR)
	$(CC) 	-I$(INC_DIR) \
		$(CPPFLAGS) \
		-c $(shell find $(SRC_DIR) -type f -name $(notdir $(basename $@)).cpp) \
		-o $(OBJ_DIR)/$(notdir $@)
		

# Create build directory for objects files
$(OBJ_DIR):
	@echo $(OBJECTS)
	@mkdir $@

# Objects may not exist yet, so build when needed
.PHONY : clean

cleanDebug: clean
	@echo Clean Debug


cleanRelease: clean
	@echo Clean Release

clean:
	rm -r $(OBJ_DIR) $(OUT)
