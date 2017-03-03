AVRDUDE_PROGRAMMER=arduino
AVRDUDE_PORT=/dev/ttyACM0
AVRDUDE_SPEED=115200

ARDUINO_DIR = /home/cams7/desenv/arduino/arduino-1.6.5
ARDUINO_VARIANTS_DIR = $(ARDUINO_DIR)/hardware/arduino/avr/variants/standard
ARDUINO_CORES_DIR = $(ARDUINO_DIR)/hardware/arduino/avr/cores/arduino

#SILENT ?= @
CROSS ?= avr-

MCU ?= atmega328p
F_CPU ?= 16000000UL

INCLUDE_DIR = include
SRC_DIR = src
CORE_DIR = core
LIB_DIR = lib

TARGET = main

MAIN_C_FILE = $(SRC_DIR)/$(TARGET).c
MAIN_CPP_FILE = $(SRC_DIR)/$(TARGET).cpp

ELF_FILE = $(CORE_DIR)/$(TARGET).elf
HEX_FILE = $(CORE_DIR)/$(TARGET).hex
EEP_FILE = $(CORE_DIR)/$(TARGET).eep
MAP_FILE = $(CORE_DIR)/$(TARGET).map
LSS_FILE = $(CORE_DIR)/$(TARGET).lss

MKDIR_P = mkdir -p
