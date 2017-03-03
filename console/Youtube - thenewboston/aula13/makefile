# rm -r obj/Linux
# mkdir -p obj/Linux 
# g++ -Wall -fexceptions -g  -c main.cpp -o obj/Linux/main.o

# rm -r bin/Linux
# mkdir -p bin/Linux 
# g++  -o bin/Linux/aula01 obj/Linux/main.o 
# ./bin/Linux/aula13

MKDIR_P = mkdir -p
RM_R = rm -r

# the compiler: g++ for C++ program
CC = g++

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -Wall -fexceptions -g

# the build target executable:
TARGET = main

CPP_FILE = $(TARGET).cpp

OBJ_DIR = obj/Linux
OBJ_FILE = $(OBJ_DIR)/$(TARGET).o

BIN_DIR = bin/Linux
BIN_FILE = $(BIN_DIR)/aula13

run: all
	./$(BIN_FILE)

all: $(BIN_FILE)
$(OBJ_FILE): $(CPP_FILE) mkObjDir
	@echo "Create object files: $(OBJ_FILE)"
	$(CC) $(CFLAGS) -c $(CPP_FILE) -o $(OBJ_FILE)

$(BIN_FILE): $(OBJ_FILE) mkBinDir
	@echo "Create bin file '$(BIN_FILE)'"
	$(CC) -o $(BIN_FILE) $(OBJ_FILE)
	
mkObjDir: rmObjDir
	@echo "Create dir '$(OBJ_DIR)'"
	$(MKDIR_P) $(OBJ_DIR)
	
mkBinDir: rmBinDir
	@echo "Create dir '$(BIN_DIR)'"
	$(MKDIR_P) $(BIN_DIR)
	
clean: rmObjDir rmBinDir

rmObjDir:
	@echo "Remove dir '$(OBJ_DIR)'"
	if test -d $(OBJ_DIR); then $(RM_R) $(OBJ_DIR); fi	
	
rmBinDir:
	@echo "Remove dir '$(BIN_DIR)'"
	if test -d $(BIN_DIR); then $(RM_R) $(BIN_DIR); fi