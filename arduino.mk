ARDUINO_HARDWARE_DIR = C:/Users/cams7/desenv/embarcado/arduino/arduino-1.0.6/hardware/arduino
ARDUINO_VARIANTS_DIR = $(ARDUINO_HARDWARE_DIR)/variants/standard
ARDUINO_CORES_DIR = $(ARDUINO_HARDWARE_DIR)/cores/arduino
ARDUINO_LIBC_DIR = $(ARDUINO_CORES_DIR)/avr-libc

CORES_SRCS_CPP = WString.cpp WMath.cpp USBCore.cpp Tone.cpp Stream.cpp Print.cpp new.cpp IPAddress.cpp HID.cpp  HardwareSerial.cpp CDC.cpp
CORES_SRCS_C = wiring_shift.c wiring_pulse.c wiring_digital.c wiring_analog.c wiring.c WInterrupts.c
LIBC_SRCS = malloc.c realloc.c