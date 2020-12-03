/*
 * Aufgabe4.c
 *
 * Created: 03.12.2020 17:01:25
 * Author : Gruppe3
 */ 

// This code waits for a character and transmits the character back (with interrupts)

#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdint.h>                     // needed for uint8_t
#include <util/delay.h>

#include <avr/interrupt.h>



#define FOSC 16000000                       // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD -1


volatile char ReceivedChar;

typedef void (*mypointer_t)(uint8_t);
volatile mypointer_t meinefunktion;

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



void callback(uint8_t c){
	sendChar(c);
}

void setup(mypointer_t pointer){
	meinefunktion = pointer;
	/*Set baud rate */
	UBRR0H = (MYUBRR >> 8);
	UBRR0L = MYUBRR;
	
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);      // Enable receiver and transmitter
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);    // Set frame: 8data, 1stp
	
	UCSR0B |= (1 << RXCIE0);	// Enable receiver Interrupt
	sei();						// Enable Interrupts globally
	
	_delay_ms(5000);		//delay to open the serial monitor
	
	sendStringNewLine((uint8_t*)"Hallo Welt!");
	sendStringNewLine((uint8_t*)"Hallo Welt!");
}

int main( void )
{
	setup(callback);
	while(1)
	{
		;                                      // Main loop
	}
}


ISR (USART_RX_vect)
{
	meinefunktion(UDR0);
//	UDR0 = 'a';
//	ReceivedChar = UDR0;                       // Read data from the RX buffer
//	while ( !(UCSR0A & (1 << UDRE0)));
//	UDR0 = ReceivedChar;                       // Write the data to the TX buffer
}


