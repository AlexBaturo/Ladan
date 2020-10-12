/*
 * ADCs.h
 *
 * Created: 03.04.2020 2:13:26
 *  Author: 111
 */ 

#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>
#include <avr/interrupt.h>

#include "ButtonDiods.h"


void initADC();
void testADC();
void resetAdc();



#endif /* ADC_H_ */



