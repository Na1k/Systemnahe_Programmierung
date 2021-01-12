/*
 * setupHWInterrupt.h
 *
 * Created: 28.11.2020 18:17:48
 * Author: Gruppe3
 */

#ifndef HWINTERRUPTSETUP_H_
#define HWINTERRUPTSETUP_H_

static inline void hardwareInterruptSetup()
{
	// D2 and D3 as Input (D2 and D3 are the HardwareInt pins)
	CLEAR_BIT(DDRD, DDD2);
	CLEAR_BIT(DDRD, DDD3);

	// Pull up for D2 and D3
	SET_BIT(PORTD, PORTD2);
	SET_BIT(PORTD, PORTD3);

	SET_BIT(EICRA, ISC00);	//sets ISC of INT0 and INT1 to 01 (any logic change)
	SET_BIT(EICRA, ISC10);
	
	SET_BIT(EIMSK, INT0);	//activates INT0 and INT1 channel
	SET_BIT(EIMSK, INT1);

	//enable interrupts
	sei();
}

#endif /* HWINTERRUPTSETUP_H_ */
