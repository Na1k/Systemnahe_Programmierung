/*
 * servo.h
 *
 * Created: 09.01.2021 13:38:34
 *  Author: Gruppe3
 */ 


#ifndef SERVO_H_
#define SERVO_H_


#include <avr/io.h>
#include "../../common/bitOperations.h"
#include <util/delay.h>

void init();
void mainloop();

#endif /* SERVO_H_ */