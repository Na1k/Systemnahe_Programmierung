/*
 * ubungeins.c
 *
 * Created: 23.11.2020 11:09:05
 * Author : Gruppe3
 */

#include "IncFile.h"
/*
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define SET_BIT(PORT,BIT) PORT |= (1 << BIT)
#define CLEAR_BIT(PORT,BIT) PORT &= ~(1 << BIT)
//#define TOGGLE_BIT(PORT,BIT) PORT ^=(1<<BIT)

#define GREEN PORTB4
#define YELLOW PORTB3
#define RED PORTB2

// Funktionen fuer die Ampelsteuerung
void clearAll(){
	CLEAR_BIT(PORTB, RED);
	CLEAR_BIT(PORTB, YELLOW);
	CLEAR_BIT(PORTB, GREEN);
}

void stateRed(){
	clearAll();
	SET_BIT(PORTB, RED);
	_delay_ms(1000);
}

void stateYellow(){
	SET_BIT(PORTB, YELLOW);
	_delay_ms(500);
}

void stateGreen(){
	clearAll();
	SET_BIT(PORTB, GREEN);
	_delay_ms(1000);
	clearAll();
}


// Makros fuer die Ampelsteuerung

#define CLEAR_ALL()\
	CLEAR_BIT(PORTB, RED);\
	CLEAR_BIT(PORTB, YELLOW);\
	CLEAR_BIT(PORTB, GREEN);\


#define STATE_RED()\
	CLEAR_ALL();\
	SET_BIT(PORTB, RED);\
	_delay_ms(1000);\


#define STATE_YELLOW()\
	SET_BIT(PORTB, YELLOW);\
	_delay_ms(500);\


#define STATE_GREEN()\
	CLEAR_ALL();\
	SET_BIT(PORTB, GREEN);\
	_delay_ms(1000);\
	CLEAR_ALL();\

*/

int main(void)
{
	// Data Direction Register -> B
	DDRB |=  (1 << DDB4)|(1 << DDB3)|(1 << DDB2); // Gesetztes Bit = Ausgang
	
	    while(1)
	    {
			STATE_RED();
			STATE_YELLOW();
			STATE_GREEN();
			STATE_YELLOW();
			/*
			stateRed();
			stateYellow();
			stateGreen();
			stateYellow();
			*/
	    }
}

