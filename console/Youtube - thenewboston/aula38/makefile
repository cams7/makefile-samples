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

TARGET_CPP_FILE = $(TARGET).cpp

OBJ_DIR = obj/Linux
TARGET_OBJ_FILE = $(OBJ_DIR)/$(TARGET).o

BIN_DIR = bin/Linux
BIN_FILE = $(BIN_DIR)/aula38

run: all
	@echo "'$(BIN_FILE)' running"
	@./$(BIN_FILE)

all: mkObjDir mkBinDir $(BIN_FILE)
$(TARGET_OBJ_FILE): $(TARGET_CPP_FILE) 
#	@echo "Create object file '$@'"
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_FILE): $(TARGET_OBJ_FILE) 
#	@echo "Create bin file '$@'"
	$(CC) -o $@ $<
	
mkObjDir: rmObjDir
	@echo "Create '$(OBJ_DIR)'"
	@$(MKDIR_P) $(OBJ_DIR)
	
mkBinDir: rmBinDir
	@echo "Create '$(BIN_DIR)'"
	@$(MKDIR_P) $(BIN_DIR)
	
clean: rmObjDir rmBinDir

rmObjDir:
	@echo "Remove '$(OBJ_DIR)'"
	@if [ -d $(OBJ_DIR) ]; then $(RM_R) $(OBJ_DIR); fi;
	
rmBinDir:
	@echo "Remove '$(BIN_DIR)'"
	@if [ -d $(BIN_DIR) ]; then $(RM_R) $(BIN_DIR); fi;