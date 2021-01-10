/*
 * echo.c
 *
 * Created: 10.01.2020 12:45:56
 * Author : Gruppe3
 */ 

#include "../../common/serial.h"

static inline void echo(uint8_t c){
	sendChar(c);
}