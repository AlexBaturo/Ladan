#include "PWM.h"


pwmPinsManage::pwmPinsManage()
{
	pwmDiodeInit;
}

void pwmPinsManage::launchPwm(const uint32_t& value_red,
							  const uint32_t& value_green)
{
	if (count > max) count = 0;
	pwmMode({RED, value_red});
	pwmMode({GREEN, value_green});
	count++;
}

void pwmPinsManage::pwmMode(const struct pwmPin& p)
{
	if(count < p.value) pwmDiodeOn(p.pin);
	else pwmDiodeOff(p.pin);
}