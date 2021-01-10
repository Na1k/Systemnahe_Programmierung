/*
 * IncFile.h
 *
 * Created: 28.11.2020 18:17:48
 *  Author: Gruppe3
 */ 


#ifndef INCFILE_H_
#define INCFILE_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "../../common/bitOperations.h"

#define BUZZER PORTB4
#define BUTTON1 PIND2
#define BUTTON2 PIND3

//Toggle Timer on Button-Interrupt depending on rising/falling edge
static inline void button1Action(){
	if(PIND & (1 << BUTTON1)){
		CLEAR_BIT(TIMSK0, OCIE0A);
	}
	else{
		SET_BIT(TIMSK0, OCIE0A);
	}
}
static inline void button2Action(){
	if(PIND & (1 << BUTTON2)){
		CLEAR_BIT(TIMSK2, OCIE2A);
	}
	else{
		SET_BIT(TIMSK2, OCIE2A);
	}
}

static inline void portSetup(){
	// PB3 and PB4 as Output
	SET_BIT(DDRB, DDB4);
	SET_BIT(DDRB, DDB3);
	
	// init Buzzer as off
	CLEAR_BIT(PORTB, BUZZER);

	// D2 and D3 as Input
	CLEAR_BIT(DDRD, DDD2);
	CLEAR_BIT(DDRD, DDD3);

	// Pull up for D2 and D3
	SET_BIT(PORTD, PORTD2);
	SET_BIT(PORTD, PORTD3);
}

static inline void hardwareInterruptSetup(){
	EICRA |= (1 << ISC00) | (1 << ISC10);		//sets ISC of INT0 and INT1 to 01 (any logic change)
	EIMSK |= (1 << INT0) | (1 << INT1);			//activates INT0 and INT1 channel
}

static inline void timerInterruptSetup(){
	// Set the Timer Mode to CTC
	TCCR0A |= (1 << WGM01);
	TCCR2A |= (1 << WGM21);

	//set prescaler to 256 / 256
	TCCR0B |= (1 << CS02);
	TCCR2B |= (1 << CS21) | (1 << CS22) ;

	// Set OCR value to 70 / 249
	OCR0A = 0x46;
	OCR2A = 0xF9;

	//Set the ISR COMPA_vect
	TIMSK0 |= (1 << OCIE0A);
	TIMSK2 |= (1 << OCIE2A);
}

void init();
void mainloop();


#endif /* INCFILE_H_ */