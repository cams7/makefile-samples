-include ../common.mk

INCLUDES = Thread.h ThreadController.h
SRCS = $(INCLUDES:%.h=%.cpp)
OBJ_FILES = $(patsubst %, $(CORE_DIR)/%, $(SRCS:%.cpp=%.o))

CORE_FILE = $(LIB_DIR)/libarduino_thread.a

ifneq ($(CROSS), )
  CC = $(CROSS)gcc
  CXX = $(CROSS)g++
  AR = $(CROSS)ar
  OBJCOPY = $(CROSS)objcopy
  OBJDUMP = $(CROSS)objdump
  SIZE = $(CROSS)size
endif

CFLAGS_COMMON = -I"$(ARDUINO_VARIANTS_DIR)" -I"$(ARDUINO_CORES_DIR)"  -I"$(ARDUINO_CORES_LIBC_DIR)" -I"$(INCLUDE_DIR)"

ifneq ($(F_CPU),)
  CFLAGS_COMMON += -DF_CPU=$(F_CPU)
endif

OPT=s
CFLAGS_COMMON += -Wall -O$(OPT) -ffunction-sections -fdata-sections -ffunction-sections -fdata-sections -mmcu=$(MCU)

CFLAGS = $(CFLAGS_COMMON) -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
CXXFLAGS = $(CFLAGS_COMMON) -fno-exceptions -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"

all: size

size: $(CORE_FILE)
	$(SILENT) $(SIZE) --format=avr --mcu=$(MCU) $<

ifneq ($(wildcard $(OBJ_FILES) $(OBJ_FILES:%.o=%.d) $(OBJ_FILES:%.o=%.lst) $(CORE_FILE) $(CORE_FILE:%.a=%.lss)), )
clean:
	-rm $(wildcard $(OBJ_FILES) $(OBJ_FILES:%.o=%.d) $(OBJ_FILES:%.o=%.lst) $(CORE_FILE) $(CORE_FILE:%.a=%.lss))
else
clean:
	@echo "Nothing to clean."
endif

$(LIB_DIR)/%.a : $(OBJ_FILES)
	@echo "Creating lib: " $@...
	$(SILENT) $(AR) -r  "$@" $^ 
	$(SILENT) $(OBJDUMP) -h -S $@  >"$(@:%.a=%.lss)"

$(CORE_DIR)/%.o : $(SRC_DIR)/%.cpp
	@echo "Compiling:" $@... 
	$(SILENT) $(CXX) $(CXXFLAGS)
	
$(CORE_DIR)/%.o : $(SRC_DIR)/%.c
	@echo "Compiling:" $@... 
	$(SILENT) $(CC) $(CFLAGS)