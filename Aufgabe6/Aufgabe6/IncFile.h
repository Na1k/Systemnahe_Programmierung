/*
 * IncFile.h
 *
 * Created: 09.01.2021 12:58:52
 * Author: Gruppe3
 */ 


#ifndef INCFILE_H_
#define INCFILE_H_

static inline void dimLed(uint8_t brightness){
	OCR0A = brightness;
}

void init();
void mainloop();

#endif /* INCFILE_H_ */