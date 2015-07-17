-include ../common.mk

INCLUDES = Thread.h ThreadController.h
SRCS = $(INCLUDES:%.h=%.cpp)
OBJ_FILES = $(patsubst %, $(CORE_DIR)/%, $(SRCS:%.cpp=%.o))

LIB_FILE = $(LIB_DIR)/libarduino_thread.a

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

all: $(LIB_FILE:%.a=%.lss) sizedummy

sizedummy: $(LIB_FILE)
	@echo 'Invoking: Print Size'
	$(SILENT) $(SIZE) --format=avr --mcu=$(MCU) $<
	@echo 'Finished building: $@'
	@echo ' '

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

$(CORE_DIR)/%.o : $(SRC_DIR)/%.cpp
	@echo "Compiling:" $@... 
	$(SILENT) $(CXX) $(CXXFLAGS)
	@echo ' '
	
$(CORE_DIR)/%.o : $(SRC_DIR)/%.c
	@echo "Compiling:" $@... 
	$(SILENT) $(CC) $(CFLAGS)
	@echo ' '