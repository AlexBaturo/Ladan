#ifndef CONFIG_H_
#define CONFIG_H_

#include <avr/io.h>

#include "math.h"

#define F_CPU 1000000UL
#define termoPortInit DDRD |= (1<<BATTERY)|(1<<HEATER)
#define HeaterOn PORTD |= (1<<HEATER)
#define HeaterOff PORTD &= ~(1<<HEATER)
#define BatteryOn PORTD |= (1<<BATTERY)
#define BatteryOff PORTD &= ~(1<<BATTERY)




const uint8_t GREEN = PD5;
const uint8_t RED = PD6;

//Входы для сигнала с кнопки одинарной
const uint8_t BUTTON_PIN = PD2;

//Выходы для управления 
const uint8_t HEATER = PD3;
const uint8_t BATTERY = PD4; 


//Период опроса АЦП, мс
const int TIMER_A0 = 300;

/*Период опроса кнопки, мс */
const int TIMER_A1 = 300;

//Терморез  B5761-S 103-F40
struct RES_DIV
{
	//референсное напряжение, В
	const static float AREF = 1.1;
	//Резистор в делителе, Ом
	const static float R = 10000;
	//B-value , константа из дока
	const static float B = 3988;
	//Нормальная температура резистора, К
	const static float T0 = 298;
	//Сопротивление при норм темп, Ом
	const static float R0 = 10000;

};


struct RES_DIV1
{
	//референсное напряжение, В
	const static float AREF = 1.1;
	//Резистор в делителе, Ом
	const static float R = 75000;
	//B-value , константа из дока
	const static float B = 4050;
	//Нормальная температура резистора, К
	const static float T0 = 298;
	//Сопротивление при норм темп, Ом
	const static float R0 = 10000;

};



//из мс получаем число для записи в регистр OCR
int timeToInt (const int msTime);

//переводи температуру в вольты
const float tempToVolt (const float temp);


//структура для задания разницы температуры
const float	 VoltToTemp (const float U, float POWER);

const float Uin (const float Uout);

const float	 VoltToTemp1 (const float U, float POWER);


//Выставляем температурные режимы
struct TEMPERATURE 
{
	//первый режим 
	const float HEATER1 = 85;
	//второй режим
    const float HEATER2 = 120;	
	const float HEATER_OFF = -274;
	//макс температура для батареи
    const float BATTERY = 60;

	const  float DIFFBATTERY = 10;
	const  float DIFFHEATER = 10;
};

struct COLOR_VALUES
{
	 uint32_t red;
	 uint32_t green; 
};

extern COLOR_VALUES color_values;
//делитель таймера
const int TIMER_DIVIDER = 256;

extern float tempHeater;

extern bool is_sleeping;


#endif /* CONFIG_H_ */