#ifndef CONFIG_H_
#define CONFIG_H_

#include <avr/io.h>

#include "math.h"

#define F_CPU 1000000UL
#define diodeOn(x) PORTB |= x 
#define diodeOff(x) PORTB &= ~(x) 
#define diodePortInit DDRB |= (1 << DIODE2)|(1 << DIODE1)
#define termoPortInit DDRD |= (1<<BATTERY)|(1<<HEATER)
#define HeaterOn PORTD |= (1<<HEATER)
#define HeaterOff PORTD &= ~(1<<HEATER)
#define BatteryOn PORTD |= (1<<BATTERY)
#define BatteryOff PORTD &= ~(1<<BATTERY)
#define pressSensInit DDRB &= ~(1<<PRESSURE); \
					  PORTB |= (1<<PRESSURE);
#define pressSensAns !(PINB & (1<<PRESSURE))

#define startTimerA1 TCCR1B |= (1 << CS12);  // уст делит на 256
#define stopTimerA1 TCCR1B &= ~(1 << CS12); \
					TCNT1 = 0;


//Управление нагревателями
const uint8_t HEATER = PD7;
const uint8_t BATTERY = PD3; 

//Диоды, показывающие режимы
const uint8_t DIODE1 = PB1;
const uint8_t DIODE2 = PB2;

//Вывод, куда подключен нажимной переключатель
const uint8_t PRESSURE = PB6;

//период таймера опроса АЦП, мс
const int TIMER_A0 = 300;

/*период таймера для защиты от дребезга, 
	Желательно около 1000 мс  */
const int TIMER_A1 = 1000;

//Для  B5761-S 103-F40
/*struct RES_DIV 
{
	//Референсное напряжение АЦП, В
	const static float AREF = 4.92;
	//Резистор в делителе, Ом
	const static float R = 10000;
	//Константа из доки
	const static float B = 3988;
	//Температура при норм усл, К
	const static float T0 = 298;
	//Сопротивление терморез при норм усл, Ом
	const static float R0 = 10000;

};*/

//Для KTY81/210,112
struct RES_DIV
{
	//Референсное напряжение АЦП, В
	const static float AREF = 4.92;
	//Резистор в делителе, Ом
	const static float R = 10000;
	//Константа из доки
	const static float B = -790;
	//Температура при норм усл, К
	const static float T0 = 298;
	//Сопротивление терморез при норм усл, Ом
	const static float R0 = 2000;

};


//аргумент - время, мс
float timeToFloat (const float msTime);

//аргумент - температура в цельсиях
const float tempToVolt (const float temp);


//Отклонение от заданной температуры, град
struct DIFF
{
	const static float HEATER = 0.0;
	const static float BATTERY = 0.0;
};


//Режимы работы
struct TEMPERATURE 
{
	//Напряжение при температуре 80, В
	const float HEATER1 = tempToVolt(27);
	//Напряжение при температуре 130, В
    const float HEATER2 = tempToVolt(45);	
	//Максимальная температура батареи, град
    const float BATTERY = tempToVolt(60);;
};

//Делитель таймера
const int TIMER_DIVIDER = 256;

extern float tempHeater;
extern uint8_t curDiode;




#endif /* CONFIG_H_ */