/*
 * Aufgabe3.c
 *
 * Created: 25.11.2020 16:55:15
 * Author : Gruppe3
 */
 #define SET_BIT(PORT,BIT) PORT|=(1<<BIT)
 #define CLEAR_BIT(PORT,BIT) PORT&=~(1<<BIT)
 #define TOGGLE_BIT(PORT,BIT) PORT ^=(1<<BIT)

 #define F_CPU 16000000UL
 #include <avr/io.h>
 #include <avr/interrupt.h>

 #define LED1 PORTB4	//!
 #define LED2 PORTB3
 #define BUTTON1 PIND2	//!
 #define BUTTON2 PIND3

 ISR (INT0_vect){

	 SET_BIT(PORTB, LED1);
 
 }
/*
 ISR (INT1_vect){
	 PORTB &= ~(1 << PORTB5);
 }
*/
 void init() {
	// PB3 and PB4 as Output
	SET_BIT(DDRB, DDB4);
	SET_BIT(DDRB, DDB3);
	//init LEDs as off
	CLEAR_BIT(PORTB, LED1);
	CLEAR_BIT(PORTB, LED2);

	// D2 and D3 as Input
	CLEAR_BIT(DDRD, DDD2);
	CLEAR_BIT(DDRD, DDD3);

	// Pull up for D2 and D3
	SET_BIT(PORTD, PORTD2);
	SET_BIT(PORTD, PORTD3);

	//Ports B3 and B4 Output (LOW) | Ports D2 and D3 Input (HIGH, for Pull Up)
	
	EICRA |= (1 << ISC00) | (1 << ISC10);	//sets ISC of INT0 and INT1 to 01 (any logic change)

	EIMSK |= (1 << INT0) | (1 << INT1);		//activates INT0 and INT1 channel
	sei();
 }

 void mainloop() {

 }

 int main() {
	 init();
	 while(1) {
		 mainloop();
	 }
 }
