CCOMMAND = g++
CFLAGS = -Wall -c -Wextra --std=c++11 
LINKARGS = -lpthread ./lib_osx/jobdispatcher.a
SRC_FILES = ./src/*.cpp
INC_DIRS = ./inc
EXE_NAME = 2dGame

all: compile link

compile:
	$(CCOMMAND) $(CFLAGS) -I$(INC_DIRS) $(SRC_FILES)
	
link:
	$(CCOMMAND) -o $(EXE_NAME) ./*.o $(LINKARGS)
	
clean:
	rm -rf ./*.o
	rm ./$(EXE_NAME)