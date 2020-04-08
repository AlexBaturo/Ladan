#ifndef CONFIG_H_
#define CONFIG_H_

#define diodeOn(x) PORTB |= x 
#define diodeOff(x) PORTB &= ~(x) 
#define diodePortInit DDRB |= (1 << DIODE2)|(1 << DIODE1)
#define termoSensorsPortInit DDRD |= (1<<BATTERY)|(1<<HEATER)
#define tSensorHeaterOn PORTD |= (1<<HEATER)
#define tSensorHeaterOff PORTD &= ~(1<<HEATER)
#define tSensorBatteryOn PORTD |= (1<<BATTERY)
#define tSensorBatteryOff PORTD &= ~(1<<BATTERY)

//Управление нагревателями
const uint8_t HEATER = PD7;
const uint8_t BATTERY = PD3; 

//Диоды, показывающие режимы
const uint8_t DIODE1 = PB1;
const uint8_t DIODE2 = PB2;


//период таймера опроса АЦП
const int TIMER_A0 = 200;

//период таймера для защиты от дребезга
const int TIMER_A1 = 3000;

//Референсное напряжение АЦП, В
const float	AREF = 5;

//Отклонение от заданной температуры, град
const float DIFF = 0.5;

//Максимальная температура батареи, град
const float TEMP_BATTERY = 2;

//Делитель выходного значения с АЦП,
//после деления значения получаются от 0 до AREF
const float DIV_ADC = 1024/AREF;


struct MODE 
{
	//Напряжение при температуре 80, В
	const static float MODE1 = 1;
	//Напряжение при температуре 130, В
	const static float MODE2 = 2;	
};



extern float tempHeater;
extern uint8_t curDiode;



#endif /* CONFIG_H_ */