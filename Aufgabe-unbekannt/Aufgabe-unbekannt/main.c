/*
 * sitzung3-usart.c
 *
 * Created: 30.11.2020 11:43:26
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

static inline void sendStringNewLine(uint8_t message){
	while(*message){
		sendChar(*message++);
	}
	sendChar('\r');
	sendChar('\n');
}

static inline void sendString(uint8_t message){
	while(*message){
		sendChar(*message++);
	}
}

void callback(uint8_t c){
	sendChar(c);
}

void setup(mypointer_t pointer){
	meinefunktion = callback;
	/*Set baud rate */
	UBRR0H = MYUBRR >> 8;
	UBRR0L = MYUBRR;
	
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);      // Enable receiver and transmitter
	//UCSR0B |= (1 << RXCIE0);                    // Enable receiver interrupt
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);    // Set frame: 8data, 1stp

	//sei();                                      // Lets not forget to enable interrupts =P
	_delay_ms(5000);
	//char text[]={'H','a','l','l','o',' ','W','e','l','t','!','\0'};
	char text[] = "Hallo Welt!";
	sendString(text);
	//sendEnter();
	sendString(text);
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

