/*
 * main.c
 *
 * Created: 25.11.2020 16:55:15
 * Author : Gruppe3
 */

/*
 * pinning:
 * Buzzer	= D12
 * Button 1 = D2
 * Button 2 = D3
 *
 */

#include "orgel.h"

ISR (TIMER0_COMPA_vect)  // timer0 overflow interrupt //used as oscillator
{
	TOGGLE_BIT(PORTB, BUZZER);
}

ISR (TIMER2_COMPA_vect)  // timer2 overflow interrupt //used as oscillator
{
	TOGGLE_BIT(PORTB, BUZZER);
}

 //Button1 interrupt
ISR (INT0_vect)
{ 
	button1Action();
}
 
 //Button2 interrupt
ISR (INT1_vect)
{
	 button2Action();
}

int main()
{
	init();
	while(1) {
		mainloop();
	}
}

void init()
{

	portSetup();
	hardwareInterruptSetup();
	timerInterruptSetup();
	
	//enable interrupts
	sei();
}

void mainloop()
{
}