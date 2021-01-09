/*
 * Aufgabe7.c
 *
 * Created: 09.01.2021 13:17:22
 * Author : Gruppe3
 * Task	  : 2 Taster, Servo: --> 0°, 180°
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include "IncFile.h"
#include <util/delay.h>


int main(void)
{
    setup();
    while (1) 
    {
		mainloop();
    }
}

void setup(){
	DDRB |= (1 << DDB1);
	// PB1 is now an output

	ICR1 = 4999;
//	ICR1 = 0x09C4;
	// set TOP to 2500
	OCR1A = 0;
//	OCR1A = 125;
//	// set PWM for 5% duty cycle @ 16bit

//	OCR1A = 250;
//	// set PWM for 10% duty cycle @ 16bit

	TCCR1A |= (1 << COM1A1)|(1 << COM1B1);
	// set none-inverting mode

	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM12)|(1 << WGM13);
	// set Phase corrected PWM mode using ICR1 as TOP
	
	TCCR1B |= (1 << CS10)|(1 << CS11);
	// START the timer with 64 as prescaler


}

void mainloop(){
	_delay_ms(1000);
	OCR1A = 100;
	_delay_ms(1000);
	OCR1A = 600;
}