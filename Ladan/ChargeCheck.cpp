/*
 * ChargeCheck.cpp
 *
 * Created: 08.07.2020 20:44:07
 *  Author: 111
 */ 

 #include "ChargeCheck.h"
 #include "config.h"

 void InitCharge()
 {
	DDRB &= ~((1<<PB1)|(1<<PB0));
	PORTB |= (1<<PB1)|(1<<PB0);

 }

int Signal()
{
	if(!(PINB & (1<<PB0)))  return 1;
	if(!(PINB & (1<<PB1)))  return 2;
	return 0;
}


 void Charge(int arg)
 {	
	PORTD &= !((1<<PD5)|(1<<PD6));
	if(arg == 1) PORTD |= (1<<PD5);
	if(arg == 2) PORTD |= (1<<PD6);

 }