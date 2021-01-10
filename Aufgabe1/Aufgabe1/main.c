/*
 * main.c
 *
 * Created: 23.11.2020 11:09:05
 * Author : Gruppe3
 */

/* 
 * pinning:
 * D10 red led 
 * D11 yellow led
 * D12 green led
 */



#include "trafficLight.h"

int main(void)
{
	init();
	while(1){
		mainloop();	
	}
	
}

void init(){
	// Set outputs
	SET_BIT(DDRB, DDB2);
	SET_BIT(DDRB, DDB3);
	SET_BIT(DDRB, DDB4);
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