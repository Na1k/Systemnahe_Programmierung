/*
 * Aufgabe6.c
 *
 * Created: 15.12.2020 15:16:11
 * Author : Gruppe3
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>

#include <stdint.h>                     // needed for uint8_t
#include <util/delay.h>
#include <stdlib.h>

#include <avr/interrupt.h>

volatile uint8_t ADCHvalue;    // Global variable, set to volatile if used with ISR

void dimLed(uint8_t brightness){
	OCR0A = brightness;
}

int main(void)
{
	DDRD |= (1 << DDD6);		// PD6 is now an output

	OCR0A = 128;				// set PWM for 50% duty cycle

	TCCR0A |= (1 << COM0A1);	// set none-inverting mode

	TCCR0A |= (1 << WGM01) | (1 << WGM00);		// set fast PWM Mode

	TCCR0B |= (1 << CS01);		// set prescaler to 8 and starts PWM

	ADMUX = 0;		// ADC0
	
	ADMUX |= (1 << REFS0);    // use AVcc as the reference (voltage)
	
	ADMUX |= (1 << ADLAR);    // Right adjust for 8 bit resolution
	
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // 128 prescale for 16Mhz
	ADCSRA |= (1 << ADATE);   // Set ADC Auto Trigger Enable
	
	ADCSRB = 0;               // 0 for free running mode

	ADCSRA |= (1 << ADEN);    // Enable the ADC
	ADCSRA |= (1 << ADIE);    // Enable Interrupts

	ADCSRA |= (1 << ADSC);    // Start the ADC conversion
	
	sei();		//enable interrupts (global)

    while (1) 
    {
		uint8_t ADCvalue = ADCHvalue;
		dimLed(ADCvalue); 
    }
}

ISR(ADC_vect)
{
	ADCHvalue = ADCH;          // only need to read the high value for 8 bit
	// REMEMBER: once ADCH is read the ADC will update
}

