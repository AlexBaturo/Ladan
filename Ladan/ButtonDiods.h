#ifndef BD_H_
#define BD_H_


#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>

#include "config.h"
#include "ADCs.h"

void initButtonDiodsPins();
void PCINTEnable(bool state);

#endif 