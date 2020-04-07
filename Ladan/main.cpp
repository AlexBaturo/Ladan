/*
 * Ladan.cpp
 *
 * Created: 07.04.2020 23:54:48
 * Author : 111
 */ 

#include <avr/io.h>
#include "ButtonDiods.h"


int main(void)
{
    cli();  
    initButtonDiodsPins();
    sei();
    while (1) 
    {
    }
}

