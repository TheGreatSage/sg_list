.PHONY: all clean

PROJECT_NAME ?= main

# Compiler
COMPILER_PATH ?= C:\msys64\mingw64\bin

PLATFORM ?= PLATFORM_DESKTOP

# Build mode option
BUILD_MODE ?= DEBUG

STATIC_FILE ?= l$(PROJECT_NAME).a
STATIC_INSTALL ?= build

ifeq ($(PLATFORM),PLATFORM_DESKTOP)
	ifeq ($(OS),Windows_NT)
        PLATFORM_OS=WINDOWS
        export PATH := $(COMPILER_PATH):$(PATH)
	else
        UNAMEOS=$(shell uname)
        ifeq ($(UNAMEOS),Linux)
            PLATFORM_OS=LINUX
        endif
    endif
endif

# Define default C compiler: gcc
# NOTE: define g++ compiler if using C++
CC = gcc

AR := ar -rc

# Make Program
# Define default make program: Mingw32-make
MAKE = mingw32-make

# Define compiler flags:
#  -O0                  defines optimization level (no optimization, better for debugging)
#  -O1                  defines optimization level
#  -g                   include debug information on compilation
#  -s                   strip unnecessary data from build -> do not use in debug builds
#  -Wall                turns on most, but not all, compiler warnings
#  -std=c99             defines C language mode (standard C from 1999 revision)
#  -std=gnu99           defines C language mode (GNU C from 1999 revision)
#  -Wno-missing-braces  ignore invalid warning (GCC bug 53119)
#  -D_DEFAULT_SOURCE    use with -std=c99 on Linux and PLATFORM_WEB, required for timespec
CFLAGS += -Wall -Wextra -std=c99 -D_DEFAULT_SOURCE -Wno-missing-braces


# Define include paths for required headers
INCLUDE_PATHS = -I./include/

LIBPATHS = -L./lib/

ifeq ($(BUILD_MODE),DEBUG)
    CFLAGS += -g -O0
else
    CFLAGS += -s -O1
endif

# Uncommit for raylib stuff

# LIBLINKS = -lraylib -llua -lcimgui -lrlImgui
# Define any libraries required on linking
# if you want to link libraries (libname.so or libname.a), use the -lname
ifeq ($(PLATFORM),PLATFORM_DESKTOP)
    # $(info Desktop links)
    ifeq ($(PLATFORM_OS),WINDOWS)
        # $(info windows links)
        # LIBLINKS += -lopengl32 -lgdi32 -lwinmm -lstdc++
	endif
endif

# Additional flags for compiler (if desired)
#CFLAGS += -Wextra -Wmissing-prototypes -Wstrict-prototypes
ifeq ($(PLATFORM),PLATFORM_DESKTOP)
    # -Wl,--subsystem,windows hides the console window
    ifeq ($(BUILD_MODE),RELEASE)
        CFLAGS += -Wl,--subsystem,windows
    endif
endif


# Define a recursive wildcard function
rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

ENTRY_POINT = main.c 
SRC_DIR = src
OBJ_DIR = obj

PROJECT_SOURCES = $(call rwildcard, $(SRC_DIR), *.c)
OBJS = $(ENTRY_POINT) $(PROJECT_SOURCES)
STATIC_OBS = $(PROJECT_SOURCES)


all:
	$(MAKE) $(PROJECT_NAME)

# Project target defined by PROJECT_NAME
$(PROJECT_NAME): $(OBJS)
	$(CC) -o $(PROJECT_NAME) $(OBJS) $(CFLAGS) $(INCLUDE_PATHS) $(LIBPATHS) $(LIBLINKS) -D$(PLATFORM)

# Compile source files
# NOTE: This pattern will compile every module defined on $(OBJS)
#%.o: %.c
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDE_PATHS) -D$(PLATFORM)

static:$(STATIC_OBS)
	mkdir -p $(STATIC_INSTALL)
	$(AR) $(STATIC_INSTALL)/$(STATIC_FILE) $(STATIC_OBS) 

$(STATIC_FILE):$(STATIC_OBS)
	$(CC) -o $(STATIC_INSTALL)/$(STATIC_FILE) $(STATIC_OBS) $(CFLAGS) $(INCLUDE_PATHS) -D$(PLATFORM)

# Clean everything
clean:
ifeq ($(PLATFORM),PLATFORM_DESKTOP)
    ifeq ($(PLATFORM_OS),WINDOWS)
		del *.o *.exe /s
    endif
    ifeq ($(PLATFORM_OS),LINUX)
		find -type f -executable | xargs file -i | grep -E 'x-object|x-archive|x-sharedlib|x-executable' | rev | cut -d ':' -f 2- | rev | xargs rm -fv
    endif
endif
	@echo Cleaning done