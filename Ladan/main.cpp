/*
 * Ladan.cpp
 *
 * Created: 02.04.2020 20:36:08
 * Author : 111
 */ 


#include "ButtonDiods.h"
#include "ADCs.h"
#include "Uart.h"
#include "PWM.h"
#include "ChargeCheck.h"
#include <avr/sleep.h>
#include <avr/power.h>




int main(void)
{	
	//clock_prescale_set(clock_div_1);
	cli();  // Отключение глобального прерывания
	initADC();
	initButtonDiodsPins();
	UARTInit();
	InitCharge();
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	sei();

	
	
    /* Replace with your application code */
    while (1) 
    {	
		
		wdt_disable();
		if(is_sleeping){
			sleep_enable();
			sleep_cpu();
		}
		else 
		{	
			//if(arg == 0) pwm.launchPwm(color_values.red, color_values.green);
			sleep_disable();
		}	
    }
}

