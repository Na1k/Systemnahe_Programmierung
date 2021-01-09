/*
 * Aufgabe5.c
 *
 * Created: 03.12.2020 18:44:51
 * Author : Gruppe3
 */ 
#include "SerialEcho.h"
#include "IncFile.h"

#include <stdlib.h>

//Output serial monitor: "Potti1: xxxx Potti2: xxxx"

volatile uint8_t Pot1ADCHvalue;    // Global variable, set to volatile if used with ISR
volatile uint8_t Pot1ADCLvalue;

volatile uint8_t Pot2ADCHvalue;    
volatile uint8_t Pot2ADCLvalue;



int main(void)
{
	init();
	while (1) 
    {
		mainloop();
	}
}

void init(){
	callbackPointer_t noEcho = *void;
	setupSerialCommunication(noEcho);
	ADMUX = 0;                // use ADC0
	ADMUX |= (1 << REFS0);    // use AVcc as the reference

	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // 128 prescale for 16Mhz
	ADCSRA |= (1 << ADATE);   // Set ADC Auto Trigger Enable
	
	ADCSRB = 0;               // 0 for free running mode

	ADCSRA |= (1 << ADEN);    // Enable the ADC
	ADCSRA |= (1 << ADIE);    // Enable Interrupts

	ADCSRA |= (1 << ADSC);    // Start the ADC conversion
	
	sei();
}

void mainloop(){
	char bufferPotti1[5];
	char bufferPotti2[5];
	
	uint16_t ADC1Tmp = 0;
	uint16_t ADC2Tmp = 0;
	
	uint16_t ADCvalue1;
	uint16_t ADCvalue2;
	
	ADCvalue1 = setBufferValue(Pot1ADCHvalue, Pot1ADCLvalue); 
	itoa(ADCvalue1, bufferPotti1, 10);
	
	ADCvalue2 = setBufferValue(Pot2ADCHvalue, Pot2ADCLvalue);
	itoa(ADCvalue2, bufferPotti2, 10);
	
	//output
	if(abs(ADC1Tmp - ADCvalue1) > 2 || abs(ADC2Tmp - ADCvalue2) > 2)
	{
		sendString((uint8_t*)"Potti1: ");
		sendString((uint8_t*)bufferPotti1);
		sendString((uint8_t*)" - Potti2: ");
		sendStringNewLine((uint8_t*)bufferPotti2);
		ADC1Tmp = ADCvalue1;
		ADC2Tmp = ADCvalue2;
	}
}

ISR(ADC_vect)
{
	//Important to toggle before retrieval of ADC values
	ADMUX ^= (1 << MUX0);	//toggles between ADC0 and ADC1
	// REMEMBER: once ADCH is read the ADC will update
	if(ADMUX & (1 << MUX0))
	{
		Pot2ADCLvalue = ADCL;
		Pot2ADCHvalue = ADCH;
	}
	else
	{
		Pot1ADCLvalue = ADCL;
		Pot1ADCHvalue = ADCH;
	}
}

