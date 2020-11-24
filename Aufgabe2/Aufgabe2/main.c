/*
 * Aufgabe2.c
 *
 * Created: 24.11.2020 00:17:06
 * Author : NickK
 */ 

#include <avr/io.h>
					//Register:
#define P0 PORTB0	//=> DDB0
#define P1 PORTB1	//=> DDB1
#define P2 PORTB2	//=> DDB2
#define P3 PORTB3	//=> DDB3

#define SET_BIT(PORT,BIT) PORT |= (1 << BIT)
#define CLEAR_BIT(PORT,BIT) PORT &= ~(1 << BIT)
/*
#define ALL_OUT() DDRB |=  (1 << DDB4)|(1 << DDB3)|(1 << DDB2)
#define ALL_IN() DDRB &=  ~(1 << DDB4)|~(1 << DDB3)|~(1 << DDB2)

	toLeft()
	toRight()
*/

static inline void setOutput(int portNum){ //Output
	DDRB |= (1 << portNum);
}
static inline void switchOn(int portNum){	//set Port HIGH
	setOutput(portNum);
	SET_BIT(PORTB, portNum);
}
static inline void switchOff(int portNum){	//set Port LOW
	setOutput(portNum);
	CLEAR_BIT(PORTB, portNum);
}
static inline void disconnect(int portNum){ //set Port as Input
	DDRB &= ~(1 << portNum);
}

//lets talk about it later
/*
static inline void pinInit(){
	CLEAR_BIT(PORTB, P0);
	CLEAR_BIT(PORTB, P1);
	CLEAR_BIT(PORTB, P2);
	CLEAR_BIT(PORTB, P3);
}
*/
int main(void)
{    
	while (1) 
    {
		
	}
}

