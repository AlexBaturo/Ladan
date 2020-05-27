/*
 * Ladan.cpp
 *
 * Created: 02.04.2020 20:36:08
 * Author : 111
 */ 


#include "ButtonDiods.h"
#include "ADCs.h"
#include "Uart.h"
#include <avr/sleep.h>



int main(void)
{
	cli();  // Отключение глобального прерывания
	initADC();
	initButtonDiodsPins();
	UARTInit();
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	sei();
    /* Replace with your application code */
    while (1) 
    {	
		if(is_sleeping){
			sleep_enable();
			sleep_cpu();
		}
		else sleep_disable();
    }
}

