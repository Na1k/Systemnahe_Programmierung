/*
 * orgel.h
 *
 * Created: 28.11.2020 18:17:48
 * Author: Gruppe3
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
static inline void button1Action()
{
	if(CHECK_BIT(PIND, BUTTON1)){
		CLEAR_BIT(TIMSK0, OCIE0A);
	}
	else{
		SET_BIT(TIMSK0, OCIE0A);
	}
}
static inline void button2Action()
{
	if(CHECK_BIT(PIND, BUTTON2)){
		CLEAR_BIT(TIMSK2, OCIE2A);
	}
	else{
		SET_BIT(TIMSK2, OCIE2A);
	}
}

static inline void portSetup()
{
	// PB3 and PB4 as Output
	SET_BIT(DDRB, DDB4);
	SET_BIT(DDRB, DDB3);
	
	// init Buzzer as off
	CLEAR_BIT(PORTB, BUZZER);
}

static inline void timerInterruptSetup()
{
	// Set the Timer Mode to CTC
	SET_BIT(TCCR0A, WGM01);
	SET_BIT(TCCR0A, WGM21);

	//set prescaler to 256 / 256
	SET_BIT(TCCR0B, CS02);
	
	SET_BIT(TCCR2B, CS21);
	SET_BIT(TCCR2B, CS22);
	
	// Set OCR value to 70 / 249
	OCR0A = 0x46;		//"Sound 1"
	OCR2A = 0xF9;		//"Sound 2"

	//Set the ISR COMPA_vect
	SET_BIT(TIMSK0, OCIE0A);
	SET_BIT(TIMSK2, OCIE2A);
}

void init();
void mainloop();


#endif /* INCFILE_H_ */