/*
 * sitzung3-adc.c
 *
 * Created: 30.11.2020 14:21:16
 * Author : NickK
 */ 

// this code continually scans ADC0 for an analog signal, using 16Mhz processor clock

#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdint.h>                     // needed for uint8_t
#include <util/delay.h>
#include <stdlib.h>

#include <avr/interrupt.h>

#define FOSC 16000000                       // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD -1

volatile uint8_t ADCvalue;    // Global variable, set to volatile if used with ISR

static inline void sendChar(uint8_t c){
	while ( !(UCSR0A & (1 << UDRE0)));
	UDR0 = c;
}

static inline void sendString(uint8_t *message){
	while(*message){
		sendChar(*message++);
	}
}

int main(void)
{

	ADMUX = 0;                // use ADC0
	ADMUX |= (1 << REFS0);    // use AVcc as the reference
	ADMUX |= (1 << ADLAR);    // Right adjust for 8 bit resolution

	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // 128 prescale for 16Mhz
	ADCSRA |= (1 << ADATE);   // Set ADC Auto Trigger Enable
	
	ADCSRB = 0;               // 0 for free running mode

	ADCSRA |= (1 << ADEN);    // Enable the ADC
	ADCSRA |= (1 << ADIE);    // Enable Interrupts

	ADCSRA |= (1 << ADSC);    // Start the ADC conversion

	sei();    // enable Interrupts (global)

	//Serial init
	UBRR0H = MYUBRR >> 8;
	UBRR0L = MYUBRR;

	UCSR0B |= (1 << TXEN0);						// Enable transmitter
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);    // Set frame: 8data, 1stp

	while (1)
	{
		// main loop
		
	}
}


ISR(ADC_vect)
{
	ADCvalue = ADCH;          // only need to read the high value for 8 bit
	// REMEMBER: once ADCH is read the ADC will update
	
	char buffer[4];
	itoa(ADCvalue, buffer, 10);
	sendString((uint8_t*)buffer);
	
	// if you need the value of ADCH in multiple spots, read it into a register
	// and use the register and not the ADCH

}
