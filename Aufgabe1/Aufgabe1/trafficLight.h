/*
 * trafficLight.h
 *
 * Created: 23.11.2020 23:18:55
 *  Author: Gruppe3
 */ 


#ifndef TRAFFICLIGHT_H_
#define TRAFFICLIGHT_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "../../common/bitOperations.h"

#define GREEN PORTB4
#define YELLOW PORTB3
#define RED PORTB2

static inline void clearAll(){
	CLEAR_BIT(PORTB, RED);
	CLEAR_BIT(PORTB, YELLOW);
	CLEAR_BIT(PORTB, GREEN);
}

static inline void redState(){
	clearAll();
	SET_BIT(PORTB, RED);
	_delay_ms(1000);
}

static inline void yellowState(){
	SET_BIT(PORTB, YELLOW);
	_delay_ms(500);
}

static inline void greenState(){
	clearAll();
	SET_BIT(PORTB, GREEN);
	_delay_ms(1000);
	clearAll();
}

//function-prototypes
void setup();
void mainloop();
void trafficLight();

#endif /* TRAFFICLIGHT_H_ */