#include "PWM.h"


pwmPinsManage::pwmPinsManage(uint8_t RED, uint8_t GREEN)
{
	pwmDiodeInit(RED, GREEN);
	_RED = RED;
	_GREEN = GREEN;
}

void pwmPinsManage::launchPwm(const uint32_t& value_red,
const uint32_t& value_green)
{
	if (count > max) count = 0;
	pwmMode({_RED, value_red});
	pwmMode({_GREEN, value_green});
	count++;
}

void pwmPinsManage::pwmMode(const struct pwmPin& p)
{
	if(count < p.value) pwmDiodeOn(p.pin);
	else pwmDiodeOff(p.pin);
}