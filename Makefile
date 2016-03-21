CCOMMAND = g++
CFLAGS = -Wall -c -Wextra --std=c++11 
LINKARGS = -L/usr/X11/lib -lX11 -lpthread
SRC_FILES = ./src/*.cpp ./src/*/*.cpp
INC_DIRS = -I./inc -I/usr/local/include
EXE_NAME = 2dGame

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	LINKARGS += ./lib_linux_x86/jobdispatcher.a
endif
ifeq ($(UNAME_S),Darwin)
	LINKARGS += ./lib_osx/jobdispatcher.a
endif
UNAME_P := $(shell uname -p)
ifeq ($(UNAME_P),x86_64)
    CCFLAGS += -D AMD64
endif
ifneq ($(filter %86,$(UNAME_P)),)
    CCFLAGS += -D IA32
endif
ifneq ($(filter arm%,$(UNAME_P)),)
    CCFLAGS += -D ARM
endif

all: compile link

compile:
	$(CCOMMAND) $(CFLAGS) $(INC_DIRS) $(SRC_FILES)
	
link:
	$(CCOMMAND) -o $(EXE_NAME) ./*.o $(LINKARGS)
	
clean:
	rm -rf ./*.o
	rm ./$(EXE_NAME)