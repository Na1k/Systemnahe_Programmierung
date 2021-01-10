/*
 * Aufgabe7.c
 *
 * Created: 09.01.2021 13:17:22
 * Author : Gruppe3
 * Task	  : 2 Taster, Servo: --> 0°, 180°
 */ 

/*
 * D9 servo PWM
 * Servo to VCC and GND
 */

#define F_CPU 16000000UL

#include "IncFile.h"

int main(void)
{
    init();
    while (1) 
    {
		mainloop();
    }
}

void init(){
	SET_BIT(DDRB,DDB1);		// PB1 is now an output

	//PWM Setup
	SET_BIT(TCCR1A,COM1A1);	// set none-inverting mode
	
	// set Phase corrected PWM mode using ICR1 as TOP
	SET_BIT(TCCR1A,WGM11);
	SET_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1B,WGM13);
	
	//set TOP_VALUE for 50Hz
	ICR1 = 4999;			// = (clockSpeed / frequency * prescaler) -1
							// (16000000/50 * 64) -1	
	
	// START the timer with 64 as prescaler
	SET_BIT(TCCR1B,CS10);
	SET_BIT(TCCR1B,CS11);
	
	//TODO set OCR1A to start value
}

void mainloop(){
	_delay_ms(1000);
	OCR1A = 100;
	_delay_ms(1000);
	OCR1A = 600;
}