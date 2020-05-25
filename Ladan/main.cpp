/*
 * Ladan.cpp
 *
 * Created: 02.04.2020 20:36:08
 * Author : 111
 */ 


#include "ButtonDiods.h"
#include "ADCs.h"
#include "Uart.h"



int main(void)
{
	cli();  // Отключение глобального прерывания
	initADC();
	initButtonDiodsPins();
	UARTInit();
	sei();
    /* Replace with your application code */
    while (1) 
    {	
		//testADC();
    }
}

