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
	clock_prescale_set(clock_div_16);
	cli();  // Отключение глобального прерывания
	initADC();
	initButtonDiodsPins();
	//UARTInit();
	InitCharge();
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	wdt_enable(WDTO_4S);
	bool wdtOn = false;
	sei();

	
	
    /* Replace with your application code */
    while (1) 
    {	
		
		wdt_reset();
		if(is_sleeping){

			HeaterOff;
			wdtOn = false;
			MCUSR = 0;
			wdt_disable();
			sleep_enable();
			sleep_cpu();

		}
		else 
		{	
			if (!wdtOn)
			{
				wdt_enable(WDTO_2S);
				wdtOn = true;
			}
		}	
    }
}

