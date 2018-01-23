SRC = $(wildcard src/*.cpp)
FILES = $(basename $(SRC))
CC = g++

FLAGS = -std=c++11 -lGL -lGLEW -lSDL2 -lSDL2main
OBJ = obj
OUT = 3DEngine

Debug: all
	@echo Debug Build Complete

Release :all
	@echo Release Build Complete


all: $(FILES)
	$(CC) -o $(OUT) $(wildcard $(OBJ)/*.o) $(FLAGS)

$(FILES):
	$(CC) -c $@.cpp $(FLAGS)
	mv $(notdir $@).o $(OBJ)


# Objects may not exist yet, so build when needed
.PHONY : clean

cleanDebug: clean
	@echo Clean Debug


cleanRelease: clean
	@echo Clean Release

clean:
	rm obj/* $(OUT)
