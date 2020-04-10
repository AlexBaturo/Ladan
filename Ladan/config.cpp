#include "config.h"


float timeToFloat (float msTime)
{
	return (float) (F_CPU*msTime*0.001/(2*TIMER_DIVIDER) - 1);
}
