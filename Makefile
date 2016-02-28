CCOMMAND = g++
CFLAGS = -Wall -c -Wextra --std=c++11 
LINKARGS = ./lib_linux_x86/jobdispatcher.a -L/usr/X11/lib -lX11 -lpthread
SRC_FILES = ./src/*.cpp ./src/*/*.cpp
INC_DIRS = -I./inc -I/usr/local/include
EXE_NAME = 2dGame

all: compile link

compile:
	$(CCOMMAND) $(CFLAGS) $(INC_DIRS) $(SRC_FILES)
	
link:
	$(CCOMMAND) -o $(EXE_NAME) ./*.o $(LINKARGS)
	
clean:
	rm -rf ./*.o
	rm ./$(EXE_NAME)