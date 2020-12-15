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
	setRegister();
	
	UCSR0B |= (1 << RXCIE0);	// Enable receiver Interrupt
	sei();						// Enable Interrupts globally
	
	_delay_ms(1000);		//delay to open the serial monitor
	
	sendStringNewLine((uint8_t*)"Initialized!");
}

void setupSerialCommunicationWithoutEcho(){
	setRegister();
	
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