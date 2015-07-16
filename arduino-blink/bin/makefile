-include C:/Users/cams7/desenv/github/makefile-samples/user.mk
-include C:/Users/cams7/desenv/github/makefile-samples/arduino.mk

SILENT ?= @
CROSS ?= avr-

MCU ?= atmega328p
F_CPU ?= 16000000UL

INCLUDE_DIR = ../include
SRC_DIR = ../src
BIN_DIR = .

CORE_DIR_NAME = arduino_core
CORE_DIR = $(BIN_DIR)/$(CORE_DIR_NAME)
CORE_LIBC_DIR = $(CORE_DIR)/avr-libc

CORE_OBJ_FILES = $(patsubst %, $(CORE_LIBC_DIR)/%, $(LIBC_SRCS:.c=.o)) $(patsubst %, $(CORE_DIR)/%, $(CORES_SRCS_C:.c=.o)) $(patsubst %, $(CORE_DIR)/%, $(CORES_SRCS_CPP:.cpp=.o))

TARGET = main

INCLUDES = 
INCLUDE_FILES = $(patsubst %, $(INCLUDE_DIR)/%, $(INCLUDES))

SRCS = $(TARGET).cpp $(INCLUDES:.h=.cpp)
SRC_FILES = $(patsubst %, $(SRC_DIR)/%, $(SRCS))

OBJ_FILES = $(patsubst %, $(BIN_DIR)/%, $(SRCS:.cpp=.o))

ELF_FILE = $(BIN_DIR)/$(TARGET).elf
HEX_FILE = $(BIN_DIR)/$(TARGET).hex
EEP_FILE = $(BIN_DIR)/$(TARGET).eep
MAP_FILE = $(BIN_DIR)/$(TARGET).map
LSS_FILE = $(BIN_DIR)/$(TARGET).lss

ifneq ($(CROSS), )
  CC = $(CROSS)gcc
  CXX = $(CROSS)g++
  AR = $(CROSS)ar
  OBJCOPY = $(CROSS)objcopy
  OBJDUMP = $(CROSS)objdump
  SIZE = $(CROSS)size
endif

CFLAGS_COMMON = -I"$(ARDUINO_VARIANTS_DIR)" -I"$(ARDUINO_CORES_DIR)"  -I"$(ARDUINO_LIBC_DIR)" -I"$(INCLUDE_DIR)"

ifneq ($(F_CPU),)
  CFLAGS_COMMON += -DF_CPU=$(F_CPU)
endif

OPT=s
CFLAGS_COMMON += -Wall -O$(OPT) -ffunction-sections -fdata-sections -ffunction-sections -fdata-sections -mmcu=$(MCU)

CFLAGS = $(CFLAGS_COMMON) -std=gnu99
CXXFLAGS = $(CFLAGS_COMMON) -fno-exceptions

CFLAGS_FULL = $(CFLAGS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<" 
CXXFLAGS_FULL = $(CXXFLAGS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"

LDFLAGS = -Wl,-Map=$(MAP_FILE),--cref

ifneq ($(wildcard $(OBJ_FILES) $(CORE_OBJ_FILES) $(ELF_FILE) $(HEX_FILE) $(EEP_FILE) $(MAP_FILE) $(OBJ_FILES:%.o=%.d) $(CORE_OBJ_FILES:%.o=%.d) $(OBJ_FILES:%.o=%.lst) $(CORE_OBJ_FILES:%.o=%.lst)), )
clean:
	-rm $(CORE_DIR)/lib$(CORE_DIR_NAME).a $(CORE_DIR)/lib$(CORE_DIR_NAME).lss $(LSS_FILE)
	-rm $(wildcard $(OBJ_FILES) $(CORE_OBJ_FILES) $(ELF_FILE) $(HEX_FILE) $(EEP_FILE) $(MAP_FILE) $(OBJ_FILES:%.o=%.d) $(CORE_OBJ_FILES:%.o=%.d) $(OBJ_FILES:%.o=%.lst) $(CORE_OBJ_FILES:%.o=%.lst))
else
clean:
	@echo "Nothing to clean."
endif

all: $(ELF_FILE) size

size: $(ELF_FILE)
	$(SILENT) $(SIZE) --format=avr --mcu=$(MCU) $<

#.SECONDARY:

$(BIN_DIR)/%.elf: $(OBJ_FILES) lib$(CORE_DIR_NAME)
	@echo "Linking:" $@..
	$(SILENT) $(CXX) --cref -s -O$(OPT) -o"$@" $(OBJ_FILES) -l$(CORE_DIR_NAME) -mrelax -Wl,--gc-sections -Wl,--gc-sections -L"$(CORE_DIR)" -mmcu=$(MCU) -lm $(LDFLAGS)
	$(SILENT) $(OBJDUMP) -h -S $@  >"$(<:%.o=%.lss)"

coreSize: lib$(CORE_DIR_NAME)
	$(SILENT) $(SIZE) --format=avr --mcu=$(MCU) $(CORE_DIR)/$<.a

lib$(CORE_DIR_NAME) : $(CORE_OBJ_FILES)
	@echo "Creating lib:" $(CORE_DIR)/$@.a...
	$(SILENT) $(AR) -r  "$(CORE_DIR)/$@.a" $^ 
	$(SILENT) $(OBJDUMP) -h -S $(CORE_DIR)/$@.a  >"$(CORE_DIR)/$@.lss"

$(CORE_DIR)/%.o : $(ARDUINO_CORES_DIR)/%.cpp
	@echo "[$(TARGET)] Compiling:" $@... 
	$(SILENT) $(CXX) $(CXXFLAGS_FULL)
		
$(CORE_DIR)/%.o : $(ARDUINO_CORES_DIR)/%.c
	@echo "[$(TARGET)] Compiling:" $@...
	$(SILENT) $(CC) $(CFLAGS_FULL)
	
$(CORE_LIBC_DIR)/%.o : $(ARDUINO_LIBC_DIR)/%.c
	@echo "[$(TARGET)] Compiling:" $@...
	$(SILENT) $(CC) $(CFLAGS_FULL)

$(BIN_DIR)/%.o : $(SRC_DIR)/%.cpp
	@echo "[$(TARGET)] Compiling:" $@... 
	$(SILENT) $(CXX) $(CXXFLAGS_FULL)

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

$(BIN_DIR)/%.hex: $(BIN_DIR)/%.elf
	@echo "Creating flash file:" $@...
	$(SILENT) $(OBJCOPY) -O ihex -R .eeprom $< $@

$(BIN_DIR)/%.eep: $(BIN_DIR)/%.elf
	@echo "Creating eeprom file:" $@...
	$(SILENT) $(OBJCOPY) -j .eeprom --set-section-flags=.eeprom="alloc,load" \
	--change-section-lma .eeprom=0 -O ihex $< $@
else
FLASH_MSG="You need to set AVRDUDE_PROGRAMMER/AVRDUDE_PORT/AVRDUDE_SPEED in ~/user.mk"
flash:
	@echo $(FLASH_MSG)

fuse:
	@echo $(FLASH_MSG)
endif

###############

# Check which .o files we already have and include their dependency files.
PRIOR_OBJS := $(wildcard $(OBJ_FILES))
include $(PRIOR_OBJS:%.o=%.d)