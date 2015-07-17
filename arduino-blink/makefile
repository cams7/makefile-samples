ifeq ($(OS),Windows_NT)
	-include ../common-win.mk 
else
	-include ../common.mk
endif

ARDUINO_CORE_NAME = arduino_core
ARDUINO_CORE_DIR = ../arduino
ARDUINO_CORE_LIB_DIR = $(ARDUINO_CORE_DIR)/lib

ARDUINO_THREAD_NAME = arduino_thread
ARDUINO_THREAD_DIR = ../arduino-thread
ARDUINO_THREAD_LIB_DIR = $(ARDUINO_THREAD_DIR)/lib
ARDUINO_THREAD_INCLUDE_DIR = $(ARDUINO_THREAD_DIR)/$(INCLUDE_DIR)

SRCS = $(shell for file in `find $(SRC_DIR) -maxdepth 1 -name *.cpp -printf "%f "`;do echo $$file; done)
OBJ_FILES = $(patsubst %, $(CORE_DIR)/%, $(SRCS:%.cpp=%.o))

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
CFLAGS_COMMON += -I"$(ARDUINO_THREAD_INCLUDE_DIR)" -I"$(INCLUDE_DIR)"

ifneq ($(F_CPU),)
  	CFLAGS_COMMON += -DF_CPU=$(F_CPU)
endif

OPT=s
CFLAGS_COMMON += -Wall -O$(OPT) -ffunction-sections -fdata-sections -ffunction-sections -fdata-sections -mmcu=$(MCU)
CFLAGS_SUFFIX = -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"

CFLAGS = $(CFLAGS_COMMON) -std=gnu99 $(CFLAGS_SUFFIX) 
CXXFLAGS = $(CFLAGS_COMMON) -fno-exceptions $(CFLAGS_SUFFIX)

LDFLAGS = -s -O$(OPT) -o"$@" $^ -l$(ARDUINO_CORE_NAME) -l$(ARDUINO_THREAD_NAME) -lm -Wl,-Map,$(@:%.elf=%.map),--cref -mrelax -Wl,--gc-sections -Wl,--gc-sections -L"$(ARDUINO_CORE_LIB_DIR)" -L"$(ARDUINO_THREAD_LIB_DIR)" -mmcu=$(MCU)

all: mkdir $(LSS_FILE) sizedummy

sizedummy: $(ELF_FILE)
	@echo "Invoking: Print Size"
	$(SILENT) $(SIZE) --format=avr --mcu=$(MCU) $<
	@echo "Finished building: $@"
	@echo ' '
	
ifeq ($(wildcard $(CORE_DIR) $(LIB_DIR)), )	
mkdir:
	@echo "Create dirs $(CORE_DIR) $(LIB_DIR)" 
	$(MKDIR_P) $(CORE_DIR) $(LIB_DIR)
	@echo ' '
else
mkdir:
endif

ifneq ($(wildcard $(OBJ_FILES) $(ELF_FILE) $(HEX_FILE) $(EEP_FILE) $(MAP_FILE) $(LSS_FILE) $(OBJ_FILES:%.o=%.d) $(OBJ_FILES:%.o=%.lst)), )
clean:
	-rm $(wildcard $(OBJ_FILES) $(ELF_FILE) $(HEX_FILE) $(EEP_FILE) $(MAP_FILE) $(LSS_FILE) $(OBJ_FILES:%.o=%.d) $(OBJ_FILES:%.o=%.lst))
	@echo ' '
else
clean:
	@echo "Nothing to clean."
	@echo ' '
endif

$(CORE_DIR)/%.lss: $(ELF_FILE)
	@echo 'Invoking: AVR Create Extended Listing'
	$(SILENT) $(OBJDUMP) -h -S $< >"$@"
	@echo 'Finished building: $@'
	@echo ' '

$(CORE_DIR)/%.elf: $(OBJ_FILES)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C++ Linker'
	$(SILENT) $(CXX) $(LDFLAGS)
	@echo 'Finished building target: $@'
	@echo ' '

$(CORE_DIR)/%.o : $(SRC_DIR)/%.cpp
	@echo "[$(TARGET)] Compiling:" $@... 
	$(SILENT) $(CXX) $(CXXFLAGS)
	@echo ' '
	
$(CORE_DIR)/%.o : $(SRC_DIR)/%.c
	@echo "[$(TARGET)] Compiling:" $@... 
	$(SILENT) $(CC) $(CFLAGS)
	@echo ' '

###############

## Programming

AVRDUDE := avrdude

AVRDUDE_FLAGS += -p $(MCU)
ifneq ($(AVRDUDE_PORT), )
  	AVRDUDE_FLAGS += -P $(AVRDUDE_PORT)
endif
ifneq ($(AVRDUDE_PROGRAMMER), )
  	AVRDUDE_FLAGS += -c $(AVRDUDE_PROGRAMMER)
endif
ifneq ($(AVRDUDE_SPEED), )
  	AVRDUDE_FLAGS += -b $(AVRDUDE_SPEED)
endif

#Add more verbose output if we dont have SILENT set
ifeq ($(SILENT), )
  	AVRDUDE_FLAGS += -v -v
endif

# Fuses for internal 8MHz oscillator
ifeq ($(MCU), atmega328p)
  	AVRDUDE_WRITE_FUSE ?= -U lfuse:w:0xe2:m -U hfuse:w:0xd9:m
endif
ifeq ($(MCU), atmega88)
  	AVRDUDE_WRITE_FUSE ?= -U lfuse:w:0xe2:m -U hfuse:w:0xdf:m
endif
ifeq ($(MCU), atmega8)
  	AVRDUDE_WRITE_FUSE ?= -U lfuse:w:0xe4:m -U hfuse:w:0xd9:m 
endif
ifeq ($(MCU), $(filter $(MCU), attiny2313 attiny4313))
  	AVRDUDE_WRITE_FUSE ?= -U lfuse:w:0xE4:m
  	#AVRDUDE_WRITE_FLASH := -U lfuse:w:0x64:m #run with 1 Mhz clock #default clock mode
endif

ifneq ($(AVRDUDE_PROGRAMMER), )
flash: $(HEX_FILE) #$(EEP_FILE)
	$(AVRDUDE) $(AVRDUDE_FLAGS) -U flash:w:$(HEX_FILE)
	#$(AVRDUDE) $(AVRDUDE_FLAGS) -U eeprom:w:$(EEP_FILE)

fuse:
	$(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_WRITE_FUSE) 
	
$(CORE_DIR)/%.hex: $(ELF_FILE)
	@echo "Create Flash image (ihex format)"
	$(SILENT) $(OBJCOPY) -R .eeprom -R .fuse -R .lock -R .signature -O ihex $< "$@"
	@echo "Finished building: $@"
	@echo ' '

$(CORE_DIR)/%.eep: $(ELF_FILE)
	@echo "Create eeprom image (ihex format)"
	$(SILENT) $(OBJCOPY) -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex $< "$@"
	@echo "Finished building: $@"
	@echo ' '

else
FLASH_MSG="You need to set AVRDUDE_PROGRAMMER/AVRDUDE_PORT/AVRDUDE_SPEED in common.mk"
flash:
	@echo $(FLASH_MSG)

fuse:
	@echo $(FLASH_MSG)
endif

###############

# Check which .o files we already have and include their dependency files.
PRIOR_OBJS := $(wildcard $(OBJ_FILES))
include $(PRIOR_OBJS:%.o=%.d)
