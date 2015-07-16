-include C:/Users/cams7/desenv/github/makefile-samples/user.mk

SILENT ?= @
CROSS ?= avr-

MCU ?= atmega328p
F_CPU ?= 16000000UL

ARDUINO_DIR = C:/Users/cams7/desenv/embarcado/arduino/arduino-1.0.6
ARDUINO_VARIANTS_DIR = $(ARDUINO_DIR)/hardware/arduino/variants/standard
ARDUINO_CORES_DIR = $(ARDUINO_DIR)/hardware/arduino/cores/arduino
ARDUINO_CORES_LIBC_DIR = $(ARDUINO_CORES_DIR)/avr-libc

CORES_SRCS_CPP = WString.cpp WMath.cpp USBCore.cpp Tone.cpp Stream.cpp Print.cpp new.cpp IPAddress.cpp HID.cpp  HardwareSerial.cpp CDC.cpp
CORES_SRCS_C = wiring_shift.c wiring_pulse.c wiring_digital.c wiring_analog.c wiring.c WInterrupts.c
CORES_LIBC_SRCS = malloc.c realloc.c

CORE_DIR = core
CORE_LIBC_DIR = $(CORE_DIR)/avr-libc
LIB_DIR = lib

OBJ_FILES = $(patsubst %, $(CORE_LIBC_DIR)/%, $(CORES_LIBC_SRCS:.c=.o)) $(patsubst %, $(CORE_DIR)/%, $(CORES_SRCS_C:.c=.o)) $(patsubst %, $(CORE_DIR)/%, $(CORES_SRCS_CPP:.cpp=.o))

CORE_NAME = arduino_core

ifneq ($(CROSS), )
  CC = $(CROSS)gcc
  CXX = $(CROSS)g++
  AR = $(CROSS)ar
  OBJCOPY = $(CROSS)objcopy
  OBJDUMP = $(CROSS)objdump
  SIZE = $(CROSS)size
endif

CFLAGS_COMMON = -I"$(ARDUINO_VARIANTS_DIR)" -I"$(ARDUINO_CORES_DIR)"  -I"$(ARDUINO_CORES_LIBC_DIR)"

ifneq ($(F_CPU),)
  CFLAGS_COMMON += -DF_CPU=$(F_CPU)
endif

OPT=s
CFLAGS_COMMON += -Wall -O$(OPT) -ffunction-sections -fdata-sections -ffunction-sections -fdata-sections -mmcu=$(MCU)

CFLAGS = $(CFLAGS_COMMON) -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
CXXFLAGS = $(CFLAGS_COMMON) -fno-exceptions -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"

all: size

size: lib$(CORE_NAME)
	$(SILENT) $(SIZE) --format=avr --mcu=$(MCU) $(LIB_DIR)/$<.a

ifneq ($(wildcard $(OBJ_FILES) $(OBJ_FILES:%.o=%.d) $(OBJ_FILES:%.o=%.lst)), )
clean:
	-rm $(LIB_DIR)/lib$(CORE_NAME).a $(LIB_DIR)/lib$(CORE_NAME).lss
	-rm $(wildcard $(OBJ_FILES) $(OBJ_FILES:%.o=%.d) $(OBJ_FILES:%.o=%.lst))
else
clean:
	@echo "Nothing to clean."
endif

lib$(CORE_NAME) : $(OBJ_FILES)
	@echo "Creating lib: " $(LIB_DIR)/$@.a...
	$(SILENT) $(AR) -r  "$(LIB_DIR)/$@.a" $^ 
	$(SILENT) $(OBJDUMP) -h -S $(LIB_DIR)/$@.a  >"$(LIB_DIR)/$@.lss"

$(CORE_DIR)/%.o : $(ARDUINO_CORES_DIR)/%.cpp
	@echo "Compiling: " $@... 
	$(SILENT) $(CXX) $(CXXFLAGS)
		
$(CORE_DIR)/%.o : $(ARDUINO_CORES_DIR)/%.c
	@echo "Compiling: " $@...
	$(SILENT) $(CC) $(CFLAGS)
	
$(CORE_LIBC_DIR)/%.o : $(ARDUINO_CORES_LIBC_DIR)/%.c
	@echo "Compiling: " $@...
	$(SILENT) $(CC) $(CFLAGS)