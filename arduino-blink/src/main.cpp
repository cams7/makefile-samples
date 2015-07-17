/*
 main.cpp - Main loop for Arduino sketches
 Copyright (c) 2005-2013 Arduino Team.  All right reserved.

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <Arduino.h>
#include <Thread.h>
#include <ThreadController.h>

#include <EEPROM.h>

#define BAUD_RATE 115200

#define PIN_LED                13   //Pino 13 Digital
#define PIN_BOTAO              12 //Pino 12 Digital

#define PIN_POTENCIOMETRO      0  //Pino 0 Analogico

#define WRITE_TIME   100 // 1 segundo
#define READ_TIME    5  // 1/100 segundo
#define BOTAO_TIME   100  // 1/20 segundo

//Declared weak in Arduino.h to allow user redefinitions.
int atexit(void (*func)()) {
	return 0;
}

// Weak empty variant initialization function.
// May be redefined by variant files.
void initVariant() __attribute__((weak));
void initVariant() {
}

void write(void);
void read(void);
void clear(void);

ThreadController* controll = new ThreadController();
Thread* writeThread = new Thread();
Thread* readThread = new Thread();
Thread* botaoThread = new Thread();

//uint8_t lastValuePotenciometro = 0x00;
uint8_t lastValue = 0xFF;

const uint16_t TOTAL_BYTES_EEPROM = /*512*/1024;
uint16_t addressWrite = 0x0000;
uint16_t addressRead = 0x0000;
//uint16_t readAddress = writeAddress;

int main(void) {
	init();

	initVariant();

#if defined(USBCON)
	USBDevice.attach();
#endif

	setup();

	for (;;) {
		loop();
		if (serialEventRun)
			serialEventRun();
	}

	return 0;
}

void setup(void) {
	pinMode(PIN_LED, OUTPUT);

	pinMode(PIN_BOTAO, INPUT);
	digitalWrite(PIN_BOTAO, HIGH);

	Serial.begin(BAUD_RATE); //frequência da porta serial - USART

	writeThread->onRun(write);
	writeThread->setInterval(WRITE_TIME);

	readThread->onRun(read);
	readThread->setInterval(READ_TIME);

	botaoThread->onRun(clear);
	botaoThread->setInterval(BOTAO_TIME);

	controll->add(writeThread);
	controll->add(readThread);
	controll->add(botaoThread);
}

void loop(void) {
	controll->run();
}

void write(void) {
	//uint8_t potenciometroValue = map(analogRead(PIN_POTENCIOMETRO), 0, 1023, 0, 255);
	//if (potenciometroValue != lastValuePotenciometro) {
	//lastValuePotenciometro = potenciometroValue;

	EEPROM.write(addressWrite, lastValue);

	if (addressWrite == (TOTAL_BYTES_EEPROM - 1))
		addressWrite = 0x0000;
	else
		addressWrite++;

	if (lastValue == 0x00)
		lastValue = 0xFF;
	else
		lastValue--;

	digitalWrite(PIN_LED, HIGH);
	//}
}
void read(void) {
	//for (uint16_t i = 0x0000; i < TOTAL_BYTES_EEPROM; i++) {
	//if (readAddress != writeAddress) {
	//readAddress = writeAddress;

	Serial.print(addressRead);
	Serial.print("\t");
	Serial.print(EEPROM.read(addressRead), DEC);
	Serial.println();

	digitalWrite(PIN_LED, LOW);

	if (addressRead == (TOTAL_BYTES_EEPROM - 1))
		addressRead = 0x0000;
	else
		addressRead++;
	//}
	//}
}

void clear(void) {
	if (digitalRead(PIN_BOTAO) == LOW) {
		digitalWrite(PIN_LED, HIGH);
		for (uint16_t i = 0x0000; i < TOTAL_BYTES_EEPROM; i++)
			EEPROM.write(i, 0);
	}
}

