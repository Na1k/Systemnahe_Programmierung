/*
 * serial.h
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
#include "bitOperations.h"

#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD -1

typedef void (*callbackPointer_t)(uint8_t);
volatile callbackPointer_t receiverCallback;

// static inline Functions

static inline void sendChar(uint8_t c)
{
	while ( !(UCSR0A & (1 << UDRE0)));
	UDR0 = c;
}

static inline void lineBreak()
{
	sendChar('\r');
	sendChar('\n');
}

static inline void sendStringNewLine(uint8_t* message)
{
	while(*message)
	{
		sendChar(*message++);
	}
	lineBreak();
}

static inline void sendString(uint8_t* message)
{
	while(*message)
	{
		sendChar(*message++);
	}
}

static inline void setRegister()
{
	UBRR0H = (MYUBRR >> 8);
	UBRR0L = MYUBRR;
	
	SET_BIT(UCSR0B, RXEN0);		// Enable receiver
	SET_BIT(UCSR0B, TXEN0);		// Enable transmitter
	SET_BIT(UCSR0C, UCSZ01);	// Set frame: 8 bit data, 1stp
	SET_BIT(UCSR0C, UCSZ00);	// Set frame: 8 bit data, 1stp
}

// Forward Declaration
void setupSerialCallback(callbackPointer_t messageReceivedCallback);
void setupSerialNoCallback();

#endif /* SERIAL_H_ */