#include "config.h"


float timeToFloat (const float msTime)
{
	return (float) (F_CPU*msTime*0.001/(2*TIMER_DIVIDER) - 1);
}

//Расчет выходного напряжения в делителе, В
const float toVolt (const double termoRes)
{
	return RES_DIV().AREF*RES_DIV().R/(RES_DIV().R + termoRes);
}

//Функция переводит температуру в Вольты
const float	 tempToVolt (const float temp)
{
	const float T = temp + 273;//Перевод в Кельвины;
	float termoRes = RES_DIV().R0*exp(RES_DIV().B*(1/T - 1/RES_DIV().T0));
	return toVolt(termoRes);
}

//Формула для расчета B-фактора
float bValue(float T, float R)
{
	float R0 = RES_DIV().R;
	float T0 = RES_DIV().T0;
	return log(R/R0)/(1/(T+273) - 1/T0);
}