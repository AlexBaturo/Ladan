/*
 * ChargeCheck.cpp
 *
 * Created: 08.07.2020 20:44:07
 *  Author: 111
 */ 

 #include "ChargeCheck.h"
 #include "config.h"
 #include "PWM.h"
 #include "ButtonDiods.h"
 #include <avr/sleep.h>

 void PCINTEnable1(bool state)
{
	 //”правление прерыванием INT0

	 if (state)
	 {
		 PCMSK0 |= (1<<PCINT0);
		 PCICR |= (1<<PCIE0);
	 }
	 else
	 {
	
		 PCMSK0 &= ~(1<<PCINT0);
		 PCICR &= ~(1<<PCIE0);
	 }
}


 void InitCharge()
 {
	 PCINTEnable1(true);

	DDRB &= ~(1<<PB0);
	PORTB |= (1<<PB0);

	DDRB &= ~(1<<PB1);
	PORTB |= (1<<PB1);

	DDRD |= (1<<PD5);
	DDRD |= (1<<PD6);

 }

 pwmPinsManage pwm1 = pwmPinsManage(RED, GREEN);

ISR(PCINT0_vect)
{
	
	PORTD &= ~(1<<HEATER);
	PCINTEnable(false);
	while(!(PINB & (1<<PB0)))
	{
		if(!(PINB & (1<<PB1))) pwm1.launchPwm(0, 255);
		else pwm1.launchPwm(255, 150);
	}

	pwm1.launchPwm(0, 0);
	PCINTEnable(true);
	is_sleeping = true;

}