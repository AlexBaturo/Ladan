#ifndef BD_H_
#define BD_H_


#include <avr/io.h>
#include <avr/interrupt.h>

#include "config.h"

void initButtonDiodsPins();
float getTemp();

#endif 