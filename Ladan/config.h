#ifndef CONFIG_H_
#define CONFIG_H_

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

//Управление нагревателями
const uint8_t HEATER = PD7;
const uint8_t BATTERY = PD3; 

//Диоды, показывающие режимы
const uint8_t DIODE1 = PB1;
const uint8_t DIODE2 = PB2;

//Вывод, куда подключен нажимной переключатель
const uint8_t PRESSURE = PB6;

//период таймера опроса АЦП
const int TIMER_A0 = 200;

//период таймера для защиты от дребезга
const int TIMER_A1 = 3000;

//Референсное напряжение АЦП, В
const static float	AREF = 5;


//Отклонение от заданной температуры, град
struct DIFF
{
	const static float HEATER = 0.5;
	const static float BATTERY = 0.5;
};


//Режимы работы
struct TEMPERATURE 
{
	//Напряжение при температуре 80, В
	const static float HEATER1 = 1;
	//Напряжение при температуре 130, В
	const static float HEATER2 = 2;	
	//Максимальная температура батареи, град
	const static float BATTERY = 2;
};



extern float tempHeater;
extern uint8_t curDiode;



#endif /* CONFIG_H_ */