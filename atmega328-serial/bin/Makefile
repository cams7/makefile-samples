# Makefile
# (C) 2011 Akafugu Corporation
#
# This program is free software; you can redistribute it and/or modify it under the
# terms of the GNU General Public License as published by the Free Software
# Foundation; either version 2 of the License, or (at your option) any later
# version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT ANY
# WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.  See the GNU General Public License for more details.

# Define your programmer in this file: ~/user.mk
-include C:/Users/cams7/desenv/github/makefile-samples/user.mk

#SILENT ?= @
CROSS ?= avr-

MCU ?= atmega328p
F_CPU ?= 16000000UL

INCLUDE_DIR = ../include
SRC_DIR = ../src
BIN_DIR = .

OBJ_FILES = $(patsubst %, $(BIN_DIR)/%, $(SRCS:.c=.o))

TARGET = main

INCLUDES = uart.h buffer.h
INCLUDE_FILES = $(patsubst %, $(INCLUDE_DIR)/%, $(INCLUDES))

SRCS = $(TARGET).c $(INCLUDES:.h=.c)
SRC_FILES = $(patsubst %, $(SRC_DIR)/%, $(SRCS))

OBJ_FILES = $(patsubst %, $(BIN_DIR)/%, $(SRCS:.c=.o))

ELF_FILE = $(BIN_DIR)/$(TARGET).elf
HEX_FILE = $(BIN_DIR)/$(TARGET).hex
EEP_FILE = $(BIN_DIR)/$(TARGET).eep
MAP_FILE = $(BIN_DIR)/$(TARGET).map

ifneq ($(CROSS), )
  CC = $(CROSS)gcc
#  CXX = $(CROSS)g++
  OBJCOPY = $(CROSS)objcopy
  OBJDUMP = $(CROSS)objdump
  SIZE = $(CROSS)size
endif

CFLAGS = -I$(INCLUDE_DIR)

ifneq ($(F_CPU),)
  CFLAGS += -DF_CPU=$(F_CPU)
endif

# These will automatically be checked if they are set to YES
#SPECIAL_DEFS +=

## Special defines

#define CHECK_ANSWER
#  ifeq ($$($(1)), YES)
#    CFLAGS += -D$(1)
#  endif
#endef

#$(foreach i,$(SPECIAL_DEFS),$(eval $(call CHECK_ANSWER,$(i))))

##

OPT=s

CFLAGS += -g -O$(OPT) \
-ffreestanding -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums \
-Wall -Wstrict-prototypes \
-Wa,-adhlns=$(@:.o=.lst) -std=gnu99 -mmcu=$(MCU) 

LDFLAGS = -Wl,-Map=$(MAP_FILE),--cref

printAllFiles:
	@echo Include files: $(INCLUDE_FILES)
	@echo Source files: $(SRC_FILES)
	@echo Object files: $(OBJ_FILES)
	
ifneq ($(wildcard $(OBJ_FILES) $(ELF_FILE) $(HEX_FILE) $(EEP_FILE) $(MAP_FILE) $(OBJ_FILES:%.o=%.d) $(OBJ_FILES:%.o=%.lst)), )
clean:
	-rm $(wildcard $(OBJ_FILES) $(ELF_FILE) $(HEX_FILE) $(EEP_FILE) $(MAP_FILE) $(OBJ_FILES:%.o=%.d) $(OBJ_FILES:%.o=%.lst))
else
clean:
	@echo "Nothing to clean."
endif

all: $(ELF_FILE) size

size: $(ELF_FILE)
	$(SILENT) $(SIZE) -C --mcu=$(MCU) $(ELF_FILE)

#.SECONDARY:

$(BIN_DIR)/%.elf: $(OBJ_FILES)
	@echo "Linking:" $@...
	$(SILENT) $(CC) $(CFLAGS) $(OBJ_FILES) --output $@ $(LDFLAGS)

#$(BIN_DIR)/%.o : $(SRC_DIR)/%.cpp
#	@echo "[$(TARGET)] Compiling:" $@... 
#	$(SILENT) $(CXX) $(CXXFLAGS) -MMD -MF $(@:%.o=%.d) -c $< -o $@

$(BIN_DIR)/%.o : $(SRC_DIR)/%.c
	@echo "[$(TARGET)] Compiling:" $@...
	$(SILENT) $(CC) $(CFLAGS) -MMD -MF $(@:%.o=%.d) -c $< -o $@
	
#$(BIN_DIR)/%.d : $(SRC_DIR)/%.cpp
#	@echo "[$(TARGET)] Generating dependency:" $@...
#	$(SILENT) $(CXX) $(CXXFLAGS) -MM -MT $(addsuffix .o, $(basename $@)) -MF $@ $<

#$(BIN_DIR)/%.d : $(SRC_DIR)/%.c
#	@echo "[$(TARGET)] Generating dependency:" $@...
#	$(SILENT) $(CC) $(CFLAGS) -MM -MT $(addsuffix .o, $(basename $@)) -MF $@ $<

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

#OPTIBOOT_BOOTLOADER = C:/Users/cams7/desenv/embarcado/arduino/arduino-1.0.6/hardware/arduino/bootloaders/atmega/ATmegaBOOT_168_atmega328_pro_8MHz.hex
ARDUINO_BOOTLOADER = C:/Users/cams7/desenv/embarcado/arduino/arduino-1.0.6/hardware/arduino/bootloaders/atmega/ATmegaBOOT_168_atmega328_pro_8MHz.hex
AVRDUDE_UNLOCK_FUSE = -U lock:w:0x3F:m
AVRDUDE_LOCK_FUSE = -U lock:w:0x0F:m
AVRDUDE_BOOTLOADER_FUSE_INT_8MHZ = -U lfuse:w:0xe2:m -U efuse:w:0x05:m
AVRDUDE_BOOTLOADER_FUSE_EXT_16MHZ =  -U lfuse:w:0xff:m -U efuse:w:0x05:m
AVRDUDE_BOOTLOADER_FUSE_SIZE_OPTIBOOT = -U hfuse:w:0xde:m
AVRDUDE_BOOTLOADER_FUSE_SIZE_ARDUINO = -U hfuse:w:0xda:m

#bootloader_8mhz:
#	@echo "Burning bootloader..."
#	$(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_UNLOCK_FUSE)
#	$(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_BOOTLOADER_FUSE_INT) $(AVRDUDE_BOOTLOADER_FUSE_SIZE_ARDUINO)
#	$(AVRDUDE) $(AVRDUDE_FLAGS) -e -U flash:w:$(ARDUINO_BOOTLOADER_8MHz)
#	$(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_LOCK_FUSE)

bootloader_16mhz:
	@echo "Burning bootloader..."
	$(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_UNLOCK_FUSE)
	$(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_BOOTLOADER_FUSE_EXT_16MHZ) $(AVRDUDE_BOOTLOADER_FUSE_SIZE_ARDUINO)
	$(AVRDUDE) $(AVRDUDE_FLAGS) -e -U flash:w:$(ARDUINO_BOOTLOADER)
	$(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_LOCK_FUSE)

#optiboot_8mhz:
#	@echo "Burning bootloader..."
#	$(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_UNLOCK_FUSE)
#	$(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_BOOTLOADER_FUSE_INT_8MHZ) $(AVRDUDE_BOOTLOADER_FUSE_SIZE_OPTIBOOT)
#	$(AVRDUDE) $(AVRDUDE_FLAGS) -e -U flash:w:$(OPTIBOOT_BOOTLOADER)
#	$(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_LOCK_FUSE)

#optiboot_16mhz:
#	@echo "Burning bootloader..."
#	$(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_UNLOCK_FUSE)
#	$(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_BOOTLOADER_FUSE_EXT_16MHZ) $(AVRDUDE_BOOTLOADER_FUSE_SIZE_OPTIBOOT)
#	$(AVRDUDE) $(AVRDUDE_FLAGS) -e -U flash:w:$(OPTIBOOT_BOOTLOADER)
#	$(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_LOCK_FUSE)


###############

# Check which .o files we already have and include their dependency files.
PRIOR_OBJS := $(wildcard $(OBJ_FILES))
include $(PRIOR_OBJS:%.o=%.d)