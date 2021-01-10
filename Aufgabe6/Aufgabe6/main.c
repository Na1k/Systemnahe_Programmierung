/*
 * Aufgabe6
 *
 * Created: 15.12.2020 15:16:11
 * Author : Gruppe3
 */ 

/*
 * A0 output Potti
 * Potti to GND and VCC
 * D6 Led
 */
#include "pwmLed.h"
volatile uint8_t ADCvalue;	// Global variable, set to volatile if used with ISR

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
	SET_BIT(DDRD,DDD6);		// PD6 is now an output

	//PWM Setup
	SET_BIT(TCCR0A,COM0A1);	// set none-inverting mode
	
	SET_BIT(TCCR0A,WGM00);	// set to fast PWM Mode
	SET_BIT(TCCR0A,WGM01);	//  |

	SET_BIT(TCCR0B,CS01);	// set prescaler to 8 and starts PWM

	setup8bitADC();
}

void mainloop()
{
	dimLed(ADCvalue);
}

ISR(ADC_vect)
{
	// REMEMBER: once ADCH is read the ADC will update
	ADCvalue = ADCH;		// only need to read the high value for 8 bit
}

