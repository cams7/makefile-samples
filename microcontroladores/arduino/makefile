ifeq ($(OS),Windows_NT)
	-include ../common-win.mk 
else
	-include ../common.mk
endif

CORES_SRCS = $(shell for file in `find $(ARDUINO_CORES_DIR) -type f`; do echo $$file; done)
CORES_SRCS_CPP = $(filter $(ARDUINO_CORES_DIR)/%.cpp, $(CORES_SRCS))
CORES_SRCS_C = $(filter $(ARDUINO_CORES_DIR)/%.c, $(CORES_SRCS))

OBJ_FILES = $(patsubst $(ARDUINO_CORES_DIR)/%, $(CORE_DIR)/%, $(CORES_SRCS_CPP:%.cpp=%.o)) $(patsubst $(ARDUINO_CORES_DIR)/%, $(CORE_DIR)/%, $(CORES_SRCS_C:%.c=%.o))

LIB_FILE = $(LIB_DIR)/libarduino_core.a

ifneq ($(CROSS), )
	CC = $(CROSS)gcc
  	CXX = $(CROSS)g++
  	AR = $(CROSS)ar
  	OBJCOPY = $(CROSS)objcopy
  	OBJDUMP = $(CROSS)objdump
  	SIZE = $(CROSS)size
endif

CFLAGS_COMMON = -I"$(ARDUINO_VARIANTS_DIR)" -I"$(ARDUINO_CORES_DIR)"

ifneq ($(F_CPU),)
  	CFLAGS_COMMON += -DF_CPU=$(F_CPU)
endif

OPT=s
CFLAGS_COMMON += -Wall -O$(OPT) -ffunction-sections -fdata-sections -ffunction-sections -fdata-sections -mmcu=$(MCU)
CFLAGS_SUFFIX = -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"

CFLAGS = $(CFLAGS_COMMON) -std=gnu99 $(CFLAGS_SUFFIX)
CXXFLAGS = $(CFLAGS_COMMON) -fno-exceptions $(CFLAGS_SUFFIX)
	
all: mkdir $(LIB_FILE:%.a=%.lss) sizedummy

sizedummy: $(LIB_FILE)
	@echo 'Invoking: Print Size'
	$(SILENT) $(SIZE) --format=avr --mcu=$(MCU) $<
	@echo 'Finished building: $@'
	@echo ' '

ifeq ($(wildcard $(CORE_DIR) $(LIB_DIR)), )	
mkdir:
	@echo "Create dirs $(CORE_DIR) $(LIB_DIR)" 
	$(MKDIR_P) $(CORE_DIR) $(LIB_DIR)
	@echo ' '
else
mkdir:
endif	

ifneq ($(wildcard $(OBJ_FILES) $(OBJ_FILES:%.o=%.d) $(OBJ_FILES:%.o=%.lst) $(LIB_FILE) $(LIB_FILE:%.a=%.lss)), )
clean:
	-rm $(wildcard $(OBJ_FILES) $(OBJ_FILES:%.o=%.d) $(OBJ_FILES:%.o=%.lst) $(LIB_FILE) $(LIB_FILE:%.a=%.lss))
	@echo ' '
else
clean:
	@echo 'Nothing to clean.'
	@echo ' '
endif

$(LIB_DIR)/%.lss: $(LIB_FILE)
	@echo 'Invoking: AVR Create Extended Listing'
	$(SILENT) $(OBJDUMP) -h -S $< >"$@"
	@echo 'Finished building: $@'
	@echo ' '
	
$(LIB_DIR)/%.a: $(OBJ_FILES)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR Archiver'
	$(SILENT) $(AR) -r  "$@" $^
	@echo 'Finished building target: $@'
	@echo ' '

$(CORE_DIR)/%.o : $(ARDUINO_CORES_DIR)/%.cpp
	@echo "Building file: $<"
	@echo "Invoking: AVR C++ Compiler"
	$(SILENT) $(CXX) $(CXXFLAGS)
	@echo "Finished building: $<"
	@echo ' '
		
$(CORE_DIR)/%.o : $(ARDUINO_CORES_DIR)/%.c
	@echo "Building file: $<"
	@echo "Invoking: AVR Compiler"
	$(SILENT) $(CC) $(CFLAGS)
	@echo "Finished building: $<"
	@echo ' '
