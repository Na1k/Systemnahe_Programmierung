/*
 * Aufgabe5.c
 *
 * Created: 03.12.2020 18:44:51
 * Author : Gruppe3
 */ 
#include "Serial.h"
#include <stdlib.h>
//Serial Monitor: Potti1: xxx Potti2: xxx

volatile uint8_t ADCHvalue;    // Global variable, set to volatile if used with ISR
volatile uint8_t ADCLvalue;

int main(void)
{
	setupWithoutEcho();
    ADMUX = 0;                // use ADC0
    ADMUX |= (1 << REFS0);    // use AVcc as the reference
    //ADMUX |= (1 << ADLAR);    // Right adjust for 8 bit resolution

    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // 128 prescale for 16Mhz
    ADCSRA |= (1 << ADATE);   // Set ADC Auto Trigger Enable
    
    ADCSRB = 0;               // 0 for free running mode

    ADCSRA |= (1 << ADEN);    // Enable the ADC
    ADCSRA |= (1 << ADIE);    // Enable Interrupts

    ADCSRA |= (1 << ADSC);    // Start the ADC conversion

	while (1) 
    {
		uint16_t ADCvalue = ADCHvalue << 8;
		ADCvalue += ADCLvalue;
		char buffer[5];
		itoa(ADCvalue, buffer, 10);
		sendStringNewLine((uint8_t*)buffer);
    }
}

ISR(ADC_vect)
{
	ADCLvalue = ADCL;
	ADCHvalue = ADCH;          // only need to read the high value for 8 bit
	// REMEMBER: once ADCH is read the ADC will update
	
	// if you need the value of ADCH in multiple spots, read it into a register
	// and use the register and not the ADCH

}

