/*
 * main.c
 *
 * Created: 03.12.2020 17:01:25
 * Author : Gruppe3
 */ 

/*
 * No pins used
 */

#include "echo.h"

int main( void ){
	setupSerialCallback(echo);
	while(1){}
}





