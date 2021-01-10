/*
 * bitOperations.h
 *
 * Created: 10.01.2020 12:35:10
 * Author: Gruppe3
 */ 

#ifndef BITOPERATIONS_H_
#define BITOPERATIONS_H_

#define SET_BIT(REGISTER,BIT) REGISTER|=(1<<BIT)
#define CLEAR_BIT(REGISTER,BIT) REGISTER&=~(1<<BIT)
#define TOGGLE_BIT(REGISTER,BIT) REGISTER^=(1<<BIT)

#endif /* BITOPERATIONS_H_ */