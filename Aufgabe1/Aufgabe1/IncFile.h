/*
 * IncFile.h
 *
 * Created: 23.11.2020 23:18:55
 *  Author: Gruppe3
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define SET_BIT(PORT,BIT) PORT |= (1 << BIT)
#define CLEAR_BIT(PORT,BIT) PORT &= ~(1 << BIT)

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

#endif /* INCFILE1_H_ */