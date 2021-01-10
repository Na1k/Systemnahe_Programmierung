/*
 * adcSetup.h
 *
 * Created: 03.12.2020 18:44:51
 * Author : Gruppe3
 */ 

#ifndef ADCSETUP_H_
#define ADCSETUP_H_

#include "bitOperations.h"
#include <avr/interrupt.h>

static inline void setup16bitADC()
{
		ADMUX = 0;              // use ADC0
		SET_BIT(ADMUX,REFS0);	// use AVcc as the reference

		SET_BIT(ADCSRA,ADPS0);	// |
		SET_BIT(ADCSRA,ADPS1);	// 128 prescale for 16Mhz
		SET_BIT(ADCSRA,ADPS2);	// |
		
		SET_BIT(ADCSRA,ADATE);	// Set ADC Auto Trigger Enable
		
		ADCSRB = 0;             // 0 for free running mode

		SET_BIT(ADCSRA,ADEN);	// Enable the ADC
		SET_BIT(ADCSRA,ADIE);	// Enable ADC Interrupts
		
		SET_BIT(ADCSRA,ADSC);	// Start the ADC conversion
		
		sei();
}

static inline void setup8bitADC()
{
	setup16bitADC();
	SET_BIT(ADMUX,ADLAR);      //set ADC to 8 bit mode
}


#endif  /* ADCSETUP_H_ */