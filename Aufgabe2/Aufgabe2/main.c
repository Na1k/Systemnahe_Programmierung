/*
 * Aufgabe2.c
 *
 * Created: 24.11.2020 00:17:06
 * Author : Gruppe3
 */

/*
 * D8 charlie1
 * D9 charlie2
 * D10 charlie3
 * D11 charlie4
 */

#include "charlieplexing.h" 

int main(void)
{
	while (1) 
    {
		mainloop();
	}
}


void mainloop(){
	rightToLeft();
	leftToRight();
}

//setup the "movement" of the lights
void leftToRight(){
	for(int i=(START_LED-1); i<LAST_LED-1; i++){
		applyLED(LED_STATES[i]);
		_delay_ms(200);
	}
}

void rightToLeft(){
	for(int i=(LAST_LED-1); i>=(START_LED); i--){
		applyLED(LED_STATES[i]);
		_delay_ms(200);
	}
}

//Apply the configuration of the array LED_STATES
void applyLED(const int* array){
	switchOn(&array[0]);
	switchOff(&array[1]);
	disconnect(&array[2], &array[3]);
}
