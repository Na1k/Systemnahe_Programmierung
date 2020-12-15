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

static inline void sendChar();


static inline void sendEnter(){
	char a = '\r';
	sendChar(&a);
	a = '\n';
	sendChar(&a);
}

static inline void sendChar(char* c){
	while ( !(UCSR0A & (1 << UDRE0)));
	UDR0 = *c;
}

static inline void sendString(char c[]){
	int i = 0;
	while(c[i]){
		sendChar(&c[i]);
		i++;
	}
	sendEnter();
}


int main( void )
{
	/*Set baud rate */
	UBRR0H = MYUBRR >> 8;
	UBRR0L = MYUBRR;
	
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);      // Enable receiver and transmitter
	//UCSR0B |= (1 << RXCIE0);                    // Enable receiver interrupt
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);    // Set frame: 8data, 1stp

	//sei();                                      // Lets not forget to enable interrupts =P
	_delay_ms(5000);
	char text[]={'H','a','l','l','o',' ','W','e','l','t','!','\0'};
	sendString(text);
	sendString(text);
	while(1)
	{
		;                                      // Main loop
	}
}

/*
ISR (USART_RX_vect)
{
	//UDR0 = 'a';
	ReceivedChar = UDR0;                       // Read data from the RX buffer
	while ( !(UCSR0A & (1 << UDRE0)));
	UDR0 = ReceivedChar;                       // Write the data to the TX buffer
}
*/
