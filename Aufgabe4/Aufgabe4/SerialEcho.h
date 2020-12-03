/*
 * SerialEcho.h
 *
 * Created: 03.12.2020 18:04:25
 * Author : Gruppe3
 */ 



#ifndef SERIALECHO_H_
#define SERIALECHO_H_
#include "Serial.h"

void echo(uint8_t c);
void setupEcho();
void setupWithoutEcho();

#endif /* SERIALECHO_H_ */