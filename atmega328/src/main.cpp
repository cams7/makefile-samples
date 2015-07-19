/*
 * main.cpp
 *
 *  Created on: 18/07/2015
 *      Author: cams7
 */

#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

//#include <blink.h>

#define LED_BIT PB5
#define LED_HIGH PORTB |= _BV(LED_BIT)
#define LED_LOW PORTB &= ~(_BV(LED_BIT))

int main(void) {

	uint8_t led_state = 1;
	DDRB |= (1 << LED_BIT);

	while (1) {
		if (led_state)
			LED_HIGH;
		else
			LED_LOW;

		led_state = !led_state;
		//_delay_ms(getDelayInMs());
		_delay_ms(1000);
	}

	return 0;
}

