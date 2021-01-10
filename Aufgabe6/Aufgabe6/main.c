/*
 * Aufgabe6
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

#include "pwmLed.h"
#include "../../common/adcSetup.h"

volatile uint8_t ADCHvalue;    // Global variable, set to volatile if used with ISR

int main(void)
{
	init();
	
    while (1) 
    {
		mainloop();
    }
}

void init()
{
	DDRD |= (1 << DDD6);		// PD6 is now an output

	OCR0A = 128;				// set PWM for 50% duty cycle 

	TCCR0A |= (1 << COM0A1);	// set none-inverting mode

	TCCR0A |= (1 << WGM01) | (1 << WGM00);		// set fast PWM Mode

	TCCR0B |= (1 << CS01);		// set prescaler to 8 and starts PWM

	setup8bitADC();
		
}

void mainloop()
{
	uint8_t ADCvalue = ADCHvalue;
	dimLed(ADCvalue);
}

ISR(ADC_vect)
{
	// REMEMBER: once ADCH is read the ADC will update
	ADCHvalue = ADCH;          // only need to read the high value for 8 bit
}

