/*
 * orgel.h
 *
 * Created: 28.11.2020 18:17:48
 * Author: Gruppe3
 */ 


#ifndef ORGEL_H_
#define ORGEL_H_

#include <avr/interrupt.h>
#include "../../common/bitOperations.h"
#include "../../common/hardwareInterruptSetup.h"

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
	// PB4 as Output
	SET_BIT(DDRB, DDB4);
	
	// init Buzzer as off
	CLEAR_BIT(PORTB, BUZZER);
}

static inline void timerInterruptSetup()
{
	// Set the Timer Mode to CTC (Count to a specific value, not to 255)
	SET_BIT(TCCR0A, WGM01);
	SET_BIT(TCCR0A, WGM21);

	//set prescaler to 256 / 256 for Timer0
	SET_BIT(TCCR0B, CS02);
	//prescaler for Timer2
	SET_BIT(TCCR2B, CS21);
	SET_BIT(TCCR2B, CS22);
	
	// Set OCR value to 70 / 249
	OCR0A = 0x46;		//"Sound 1"
	OCR2A = 0xF9;		//"Sound 2"
	
	sei();
}

void init();
void mainloop();


#endif /* ORGEL_H_ */
