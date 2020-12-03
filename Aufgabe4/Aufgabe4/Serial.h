/*
 * Serial.h
 *
 * Created: 03.12.2020 17:29:58
 * Author: Gruppe3
 */ 


#ifndef SERIAL_H_
#define SERIAL_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdint.h>                     // needed for uint8_t
#include <util/delay.h>

#include <avr/interrupt.h>

#define FOSC 16000000                       // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD -1

typedef void (*callbackPointer_t)(uint8_t);
volatile callbackPointer_t receiverCallback;

// static inline Functions

static inline void sendChar(uint8_t c){
	while ( !(UCSR0A & (1 << UDRE0)));
	UDR0 = c;
}

static inline void lineBreak(){
	sendChar('\r');
	sendChar('\n');
}

static inline void sendStringNewLine(uint8_t* message){
	while(*message){
		sendChar(*message++);
	}
	lineBreak();
}

static inline void sendString(uint8_t* message){
	while(*message){
		sendChar(*message++);
	}
}

// Forward Declaration
void setupSerialCommunication(callbackPointer_t messageReceivedCallback);


#endif /* SERIAL_H_ */