/*
 * serial.c
 *
 * Created: 03.12.2020 17:30:14
 * Author : Gruppe3
 */ 

#include "serial.h"

void setupSerialNoCallback()
{
	setRegister();
	
	sendStringNewLine((uint8_t*)"Initialized!");
}

void setupSerialCallback(callbackPointer_t messageReceivedCallback)
{
	receiverCallback = messageReceivedCallback;
	
	SET_BIT(UCSR0B, RXCIE0);	// Enable receiver Interrupt
	sei();						// Enable Interrupts globally
	
	setupSerialNoCallback();
}

ISR (USART_RX_vect)
{
	receiverCallback(UDR0);
}