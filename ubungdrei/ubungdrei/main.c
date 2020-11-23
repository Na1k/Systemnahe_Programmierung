/*
 * ubungdrei.c
 *
 * Created: 23.11.2020 14:31:19
 * Author : NickK
 */ 

#define SET_BIT(PORT,BIT) PORT|=(1<<BIT)
#define CLEAR_BIT(PORT,BIT) PORT&=~(1<<BIT)
#define TOGGLE_BIT(PORT,BIT) PORT ^=(1<<BIT)


#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define LED PORTB5
#define ONPIN PIND2
#define OFFPIN PIND3

ISR (INT0_vect){
	PORTB |= 1 << PORTB5;
}

ISR (INT1_vect){
	PORTB &= ~(1 << PORTB5);
}

void init() {

	// PB5 als Ausgang
	DDRB |= 0b00100000;

	// D2 und D3 als Eingang
	//CLEAR_BIT(DDRD, DDD2);
	//CLEAR_BIT(DDRD, DDD3);
	DDRD = 0;

	// Pullup für D2 und D3
	//SET_BIT(PORTD, PORTD2);
	//SET_BIT(PORTD, PORTD3);
	PORTD = 0xff;

	// BuiltIn LED Off
	PORTB |= 0 << PORTB5;

	EICRA |= (1 << ISC00) | (1 << ISC01)  | (1 << ISC10)  | (1 << ISC11); //sets ISC of INT0 and INT1 to 11 (rising edge)

	EIMSK |= (1 << INT0) | (1 << INT1); //activates INT0 and INT1 channel
	sei();

}

void mainloop() {

}

	int main() {
	init();
	while(1) {
	mainloop();
	}
}

