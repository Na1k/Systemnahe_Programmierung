/*
 * Serial.c
 *
 * Created: 03.12.2020 17:30:14
 * Author : Gruppe3
 */ 

#include "Serial.h"

void setupSerialCommunication(callbackPointer_t messageReceivedCallback){
	receiverCallback = messageReceivedCallback;
	/*Set baud rate */
	UBRR0H = (MYUBRR >> 8);
	UBRR0L = MYUBRR;
	
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);      // Enable receiver and transmitter
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);    // Set frame: 8data, 1stp
	
	UCSR0B |= (1 << RXCIE0);	// Enable receiver Interrupt
	sei();						// Enable Interrupts globally
	
	_delay_ms(5000);		//delay to open the serial monitor
	
	sendStringNewLine((uint8_t*)"Initialized!");
}

ISR (USART_RX_vect)
{
	receiverCallback(UDR0);
	//	UDR0 = 'a';
	//	ReceivedChar = UDR0;                       // Read data from the RX buffer
	//	while ( !(UCSR0A & (1 << UDRE0)));
	//	UDR0 = ReceivedChar;                       // Write the data to the TX buffer
}