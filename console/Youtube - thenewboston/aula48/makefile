# rm -r obj/Linux 
# mkdir -p obj/Linux
# g++ -Wall -fexceptions -O2 -Iinclude -c main.cpp -o obj/Linux/main.o

# rm -r obj/Linux/src
# mkdir -p obj/Linux/src
# g++ -Wall -fexceptions -O2 -Iinclude -c src/Burrito.cpp -o obj/Linux/src/Burrito.o

# rm -r bin/Linux
# mkdir -p bin/Linux
# g++ -o bin/Linux/aula15 obj/Linux/main.o obj/Linux/src/Burrito.o
# ./bin/Linux/aula15

MKDIR_P = mkdir -p
RM_R = rm -r

# the compiler: g++ for C++ program
CC = g++

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -Wall -fexceptions -O2 -Iinclude

# the build target executable:
TARGET = main
TARGET_CPP_FILE = $(TARGET).cpp

OBJ_DIR = obj/Linux
TARGET_OBJ_FILE = $(OBJ_DIR)/$(TARGET).o

INCLUDE_CPP_DIR = src
INCLUDE_FILES = $(shell for file in `find $(INCLUDE_CPP_DIR) -type f`; do echo $$file; done)
INCLUDE_CPP_FILES = $(filter $(INCLUDE_CPP_DIR)/%.cpp, $(INCLUDE_FILES))

INCLUDE_OBJ_FILES = $(patsubst $(INCLUDE_CPP_DIR)/%, $(OBJ_DIR)/%, $(INCLUDE_CPP_FILES:%.cpp=%.o))

BIN_DIR = bin/Linux
BIN_FILE = $(BIN_DIR)/aula48

run: all
	@echo "'$(BIN_FILE)' running"
	@./$(BIN_FILE)

all: mkObjDir mkBinDir $(BIN_FILE)
$(TARGET_OBJ_FILE): $(TARGET_CPP_FILE) 
#	@echo "Create object file '$@'"
	$(CC) $(CFLAGS) -c $< -o $@
	
$(INCLUDE_OBJ_FILES): $(INCLUDE_CPP_FILES) 
#	@echo "Create object file '$@'"
	$(CC) $(CFLAGS) -c $(patsubst $(OBJ_DIR)/%, $(INCLUDE_CPP_DIR)/%, $(@:%.o=%.cpp)) -o $@
	
$(BIN_FILE): $(TARGET_OBJ_FILE) $(INCLUDE_OBJ_FILES)
#	@echo "Create bin file '$@'"
	$(CC) -o $@ $^
	
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