/*
 * sitzung3-pwm.c
 *
 * Created: 30.11.2020 09:33:08
 * Author : Gruppe3
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

void dimUp(){
	for(int i=0; i<255;i+=10){
		OCR0A = (uint8_t)i;
		_delay_ms(100);
	}
	
}

void dimDown(){
	for(int i=255; i>0; i-=10){
		OCR0A = (uint8_t)i;
		_delay_ms(100);
	}
}

int main(void)
{
	DDRD |= (1 << DDD6);
	// PD6 is now an output

	OCR0A = 0;
	// set PWM for 50% duty cycle


	TCCR0A |= (1 << COM0A1);
	// set none-inverting mode

	TCCR0A |= (1 << WGM01) | (1 << WGM00);
	// set fast PWM Mode

	TCCR0B |= (1 << CS01);
	// set prescaler to 8 and starts PWM


	while (1)
	{
		dimUp();
		dimDown();
		//OCR0A = 192;
		//_delay_ms(1000);
		//OCR0A = 64;
		//_delay_ms(1000);
	}
}

