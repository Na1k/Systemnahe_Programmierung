/*
 * main.c
 *
 * Created: 23.11.2020 11:09:05
 * Author : Gruppe3
 */

#include "IncFile.h"

int main(void)
{
	setup();
	while(1){
		mainloop();	
	}
	
}

void setup(){
	// Data Direction Register -> B
	DDRB |=  (1 << DDB4)|(1 << DDB3)|(1 << DDB2); // set Bit = output
}

void mainloop(){
	trafficLight();
}

void trafficLight(){
	redState();
	yellowState();
	greenState();
	yellowState();
}