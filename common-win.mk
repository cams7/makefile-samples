AVRDUDE_PROGRAMMER=arduino
AVRDUDE_PORT=COM3
AVRDUDE_SPEED=115200

ARDUINO_DIR = C:/Users/cams7/desenv/embarcado/arduino/arduino-1.0.6
ARDUINO_VARIANTS_DIR = $(ARDUINO_DIR)/hardware/arduino/variants/standard
ARDUINO_CORES_DIR = $(ARDUINO_DIR)/hardware/arduino/cores/arduino
ARDUINO_CORES_LIBC_DIR = $(ARDUINO_CORES_DIR)/avr-libc

#SILENT ?= @
CROSS ?= avr-

MCU ?= atmega328p
F_CPU ?= 16000000UL

INCLUDE_DIR = include
SRC_DIR = src
CORE_DIR = core
LIB_DIR = lib

TARGET = main

ELF_FILE = $(CORE_DIR)/$(TARGET).elf
HEX_FILE = $(CORE_DIR)/$(TARGET).hex
EEP_FILE = $(CORE_DIR)/$(TARGET).eep
MAP_FILE = $(CORE_DIR)/$(TARGET).map
LSS_FILE = $(CORE_DIR)/$(TARGET).lss