/*
 * SerialEcho.c
 *
 * Created: 03.12.2020 18:04:11
 * Author : Gruppe3
 */ 

#include "SerialEcho.h"

void echo(uint8_t c){
	sendChar(c);
}

void setupEcho(){
	setupSerialCommunication(echo);
	sendStringNewLine((uint8_t*)"Write something to be repeated");	
}

void setupWithoutEcho(){
	setupSerialCommunicationWithoutEcho();
}