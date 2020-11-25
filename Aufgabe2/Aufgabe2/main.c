/*
 * Aufgabe2.c
 *
 * Created: 24.11.2020 00:17:06
 * Author : Gruppe3
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
					//Register:
#define P0 PORTB0	//=> DDB0
#define P1 PORTB1	//=> DDB1
#define P2 PORTB2	//=> DDB2
#define P3 PORTB3	//=> DDB3

#define LED_COUNT 12

#define SET_BIT(PORT,BIT) PORT |= (1 << BIT)
#define CLEAR_BIT(PORT,BIT) PORT &= ~(1 << BIT)

const int LED_STATES[12][4] =
//		ON,  OFF,  NOT CONNECTED,  NOT CONNECTED
{
	{	P0,  P1,   P2,			   P3           }, //LED  1
	{	P1,  P0,   P2,			   P3           }, //LED  2
	{	P1,  P2,   P0,			   P3           }, //LED  3
	{	P2,  P1,   P0,			   P3           }, //LED  4
	{	P2,  P3,   P0,			   P1           }, //LED  5
	{	P3,  P2,   P0,			   P1           }, //LED  6
	{	P0,  P2,   P1,			   P3           }, //LED  7
	{	P2,  P0,   P1,			   P3           }, //LED  8
	{	P1,  P3,   P0,			   P2           }, //LED  9
	{	P3,  P1,   P0,			   P2           }, //LED 10
	{	P0,  P3,   P1,			   P2           }, //LED 11
	{	P3,  P0,   P1,			   P2           }, //LED 12
};
//END OF INCLUDE/CONST/DEFINE ---------------------------------

//set Ports as Output/Input, set Ports HIGH/LOW

static inline void setOutput(const int* portNum){	//Output
	DDRB |= (1 << *portNum);
}
static inline void switchOn(const int* portNum){	//set Port HIGH
	setOutput(portNum);
	SET_BIT(PORTB, *portNum);
}
static inline void switchOff(const int* portNum){	//set Port LOW
	setOutput(portNum);
	CLEAR_BIT(PORTB, *portNum);
}
static inline void disconnect(const int* portNum1, const int* portNum2){	//set Port as Input
	DDRB &= ~(1 << *portNum1) & ~(1 << *portNum2);
	CLEAR_BIT(PORTB, *portNum1);
	CLEAR_BIT(PORTB, *portNum2);
}

//Apply the configuration of the array LED_STATES

static inline void applyLED(const int* array){
	switchOn(&array[0]);
	switchOff(&array[1]);
	disconnect(&array[2], &array[3]);
}

//setup the "movement" of the lights
static inline void clearAll(){
	DDRB &= ~(1 << P0) & ~(1 << P1) & ~(1 << P2) & ~(1 << P3);
}

static inline void leftToRight(){
	for(int i=0; i<LED_COUNT; i++){
		applyLED(LED_STATES[i]);
		_delay_ms(200);
		clearAll();
	}
}

static inline void rightToLeft(){
	for(int i=(LED_COUNT-1); i>=0; i--){
		applyLED(LED_STATES[i]);
		_delay_ms(200);
		clearAll();
	}
}


//END OF FUNCTIONS---------------------

//lets talk about it later --> or never

static inline void pinInit(){
	CLEAR_BIT(PORTB, P0);
	CLEAR_BIT(PORTB, P1);
	CLEAR_BIT(PORTB, P2);
	CLEAR_BIT(PORTB, P3);
}

int main(void)
{    			
	applyLED(LED_STATES[5]);
	_delay_ms(1000);
	clearAll();
	_delay_ms(500);
	while (1) 
    {
		
		rightToLeft();
		_delay_ms(1000);
		leftToRight();
		_delay_ms(1000);
		
		/*
		applyLED(LED_STATES[0]);
		_delay_ms(1000);
		applyLED(LED_STATES[1]);
		_delay_ms(1000);
		applyLED(LED_STATES[2]);
		_delay_ms(1000);
		applyLED(LED_STATES[3]);
		_delay_ms(1000);
		applyLED(LED_STATES[4]);
		_delay_ms(1000);
		applyLED(LED_STATES[5]);
		_delay_ms(1000);
		applyLED(LED_STATES[6]);
		_delay_ms(1000);
		applyLED(LED_STATES[7]);
		_delay_ms(1000);
		applyLED(LED_STATES[8]);
		_delay_ms(1000);
		applyLED(LED_STATES[9]);
		_delay_ms(1000);
		applyLED(LED_STATES[10]);
		_delay_ms(1000);
		applyLED(LED_STATES[11]);
		_delay_ms(1000);*/
	}

}

