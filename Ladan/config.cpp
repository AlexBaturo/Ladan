#include "config.h"


int timeToInt  (const int msTime)
{
	return (F_CPU*msTime*0.001/(2*TIMER_DIVIDER) - 1);
}

//Расчет выходного напряжения в делителе, В
const float toVolt (const float termoRes)
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


const float Uin (const float Uout)
{
	return Uout*(10000 + 2000)/2000;
}

const float toRes (const float Uout, const float POWER)
{
	float PWR = Uin(POWER);
	return Uout*RES_DIV().R/(PWR-Uout);
}

//Функция переводит  Вольты в температуру
const float	 VoltToTemp (const float U, float POWER)
{
	const float termoRes = toRes(U, POWER);
	float temper = 1/RES_DIV().T0 + 1/(RES_DIV().B)*log(termoRes/RES_DIV().R0);
	float realTemp = 1/temper - 273;
	return realTemp;
}