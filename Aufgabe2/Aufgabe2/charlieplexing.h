/*
 * charlieplexing.h
 *
 * Created: 28.11.2020 17:24:21
 *  Author: Gruppe3
 */ 


#ifndef CHARLIEPLEXING_H_
#define CHARLIEPLEXING_H_

//INCLUDE/CONST/DEFINE ----------------------------------------

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "../../common/bitOperations.h"

					//Register:
#define P0 PORTB0	//=> DDB0
#define P1 PORTB1	//=> DDB1
#define P2 PORTB2	//=> DDB2
#define P3 PORTB3	//=> DDB3

//in this setup:
//needs to be between 1 and 12
//START_LED < LAST_LED
#define LAST_LED 12
#define START_LED 1



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

//FUNCTIONS ---------------------------------------------------

//set Ports as Output/Input, set Ports HIGH/LOW
static inline void setOutput(const int* portNum){	//Output
	SET_BIT(DDRB, *portNum);
}
static inline void switchOn(const int* portNum){	//set Port HIGH
	setOutput(portNum);
	SET_BIT(PORTB, *portNum);
}
static inline void switchOff(const int* portNum){	//set Port LOW
	setOutput(portNum);
	CLEAR_BIT(PORTB, *portNum);
}
static inline void disconnect(const int* portNum1, const int* portNum2){	
	CLEAR_BIT(DDRB, *portNum1);					//set Port as Input
	CLEAR_BIT(DDRB, *portNum2);					//set Port as Input
	CLEAR_BIT(PORTB, *portNum1);					//to not enable the pull-up resistor
	CLEAR_BIT(PORTB, *portNum2);					//on the Input-Ports
}

//function-prototypes
void mainloop();
void setup();
void applyLED(const int* array);
void leftToRight();
void rightToLeft();

//END OF FUNCTIONS --------------------------------------------
#endif /* CHARLIEPLEXING_H_ */
