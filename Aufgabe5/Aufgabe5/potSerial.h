/*
 * IncFile.h
 *
 * Created: 09.01.2021 11:57:15
 *  Author: Gruppe3
 */ 


#ifndef INCFILE_H_
#define INCFILE_H_

static inline uint16_t convert8to16bit(uint8_t PotADCHvalue, uint8_t PotADCLvalue)
{
	uint16_t ADCvalue = PotADCHvalue << 8;
	ADCvalue += PotADCLvalue;
	return ADCvalue;
}

void init();
void mainloop();

#endif /* INCFILE_H_ */