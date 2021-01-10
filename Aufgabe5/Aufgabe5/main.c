/*
 * Aufgabe5.c
 *
 * Created: 03.12.2020 18:44:51
 * Author : Gruppe3
 */ 

/*
 * A0 output Potti1
 * A1 output Potti2
 * Potti1 and Potti2 to GND and VCC
 */


#include "../../common/serial.h"
#include "potSerial.h"
#include "../../common/adcSetup.h"

#include <stdlib.h>

//Output serial monitor: "Potti1: xxxx Potti2: xxxx"

volatile uint8_t Pot1ADCHvalue;    // Global variable, set to volatile if used with ISR
volatile uint8_t Pot1ADCLvalue;

volatile uint8_t Pot2ADCHvalue;    
volatile uint8_t Pot2ADCLvalue;

	
static uint16_t ADC1Tmp = 0;
static uint16_t ADC2Tmp = 0;

static uint16_t ADCvalue1;
static uint16_t ADCvalue2;



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
	setupSerialNoCallback();
	setup16bitADC();
}

void mainloop()
{
	char bufferPotti1[5];
	char bufferPotti2[5];
	
	ADCvalue1 = convert8to16bit(Pot1ADCHvalue, Pot1ADCLvalue); 
	itoa(ADCvalue1, bufferPotti1, 10);
	
	ADCvalue2 = convert8to16bit(Pot2ADCHvalue, Pot2ADCLvalue);
	itoa(ADCvalue2, bufferPotti2, 10);
	
	//output
	if(abs(ADC1Tmp - ADCvalue1) > 3 || abs(ADC2Tmp - ADCvalue2) > 3)
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
	TOGGLE_BIT(ADMUX, MUX0); //toggles between ADC0 and ADC1
	
	// REMEMBER: once ADCH is read the ADC will update
	if(CHECK_BIT(ADMUX,MUX0))
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

