ifeq ($(OS),Windows_NT)
	-include ../common-win.mk 
else
	-include ../common.mk
endif

CORE_LIBC_DIR = $(CORE_DIR)/avr-libc

CORES_SRCS_CPP = $(shell for file in `find $(ARDUINO_CORES_DIR) -maxdepth 1 -name *.cpp -printf "%f "`;do echo $$file; done)
CORES_SRCS_C = $(shell for file in `find $(ARDUINO_CORES_DIR) -maxdepth 1 -name *.c -printf "%f "`;do echo $$file; done)

OBJ_FILES = $(patsubst %, $(CORE_DIR)/%, $(CORES_SRCS_CPP:%.cpp=%.o)) $(patsubst %, $(CORE_DIR)/%, $(CORES_SRCS_C:%.c=%.o))
ifeq ($(OS),Windows_NT)	
	CORES_LIBC_SRCS = $(shell for file in `find $(ARDUINO_CORES_LIBC_DIR) -maxdepth 1 -name *.c -printf "%f "`;do echo $$file; done)
	OBJ_FILES += $(patsubst %, $(CORE_LIBC_DIR)/%, $(CORES_LIBC_SRCS:%.c=%.o))
endif

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
ifeq ($(OS),Windows_NT)
	CFLAGS_COMMON += -I"$(ARDUINO_CORES_LIBC_DIR)"
endif

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

ifeq ($(wildcard $(CORE_LIBC_DIR) $(LIB_DIR)), )	
mkdir:
	@echo "Create dirs $(CORE_LIBC_DIR) $(LIB_DIR)" 
	$(MKDIR_P) $(CORE_LIBC_DIR) $(LIB_DIR)
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
	@echo "Compiling: " $@... 
	$(SILENT) $(CXX) $(CXXFLAGS)
	@echo ' '
		
$(CORE_DIR)/%.o : $(ARDUINO_CORES_DIR)/%.c
	@echo "Compiling: " $@...
	$(SILENT) $(CC) $(CFLAGS)
	@echo ' '
	
ifeq ($(OS),Windows_NT)	
$(CORE_LIBC_DIR)/%.o : $(ARDUINO_CORES_LIBC_DIR)/%.c
	@echo "Compiling: " $@...
	$(SILENT) $(CC) $(CFLAGS)
	@echo ' '
endif
