/*
 * PWM.h
 *
 * Created: 06.06.2020 1:28:59
 *  Author: 111
 */ 


#ifndef PWM_H_
#define PWM_H_
#include "config.h"

#define pwmDiodeInit DDRC |= (1<<RED)|(1<<GREEN);
#define pwmDiodeOn(x) PORTC |= (1<<x)
#define pwmDiodeOff(x) PORTC &= ~(1<<x)


struct pwmPin
{
	const uint8_t pin;
	uint32_t value;
};


class pwmPinsManage
{

public:
	
	pwmPinsManage();
	void launchPwm (const uint32_t& value_red, 
					const uint32_t& value_green);
private:
	uint32_t count =0;
	const uint32_t max = 255;

	void pwmMode(const struct pwmPin& p);
};




#endif /* PWM_H_ */