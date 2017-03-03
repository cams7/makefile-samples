#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <uart.h>

#define LED_BIT PB5
#define LED_HIGH PORTB |= _BV(LED_BIT)
#define LED_LOW PORTB &= ~(_BV(LED_BIT))

void main(void) __attribute__ ((noreturn));

void main(void) {
	uint8_t led_state = 1;

	uartInit();
	uartSetBaudRate(115200);

	DDRB |= (1 << LED_BIT);
   
	while (1) {
		if (led_state) {
			uartSendBuffer("LED goes on\n", 12);
			LED_HIGH;
		}
		else {
			uartSendBuffer("LED goes off\n", 13);
			LED_LOW;
		}

		led_state = !led_state;
		_delay_ms(100);
	}
}