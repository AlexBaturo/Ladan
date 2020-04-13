#include "ButtonDiods.h"

float tempHeater;
uint8_t curDiode;

void iniTimerA1(void)
{
	// инициализация TimerA1

	OCR1A = timeToFloat(TIMER_A1); // установка регистра совпадения
	TCCR1B |= (1 << WGM12);  // включить CTC режим
	TIMSK1 |= (1 << OCIE1A);
	
}

void INT0Enable(bool state)
{
	//Управление прерыванием INT0

	EICRA &= ~(1<<ISC01)|(1<<ISC00); //включим прерывания INT0 по низкому уровню

	if (state) EIMSK |= (1<<INT0); //разрешим внешние прерывания INT0
	else EIMSK &= ~(1<<INT0);
	
}

void startCondition()
{
	curDiode = DIODE2;
	tempHeater = TEMPERATURE().HEATER1;
	diodeOn((1 << DIODE1));
	HeaterOn;
}

void initButtonDiodsPins() 
{
	/*Инициализируем выводы для диодов и кнопки,
	  включаем таймерА1 для борьбы с дребезгом,
	  настраиваем внешнее прерывание*/
	  	
	//Диоды 
	diodePortInit;

	//Начальный режим работы
	startCondition();
	
	//Включим ножку INT0 на вход
	DDRD &= ~(1<<PD2);
	
	//Подтянем резистор на ножке INT0 к питанию
	PORTD |= (1<<PD2);

	INT0Enable(true);

	iniTimerA1();
}


ISR(INT0_vect)
{	
	startTimerA1;
}


ISR (TIMER1_COMPA_vect)
{	
	diodeOff((1 << DIODE2)|(1 << DIODE1));
	diodeOn((1 << curDiode));
	
	switch(curDiode)
	{
		case DIODE1:
		tempHeater = TEMPERATURE().HEATER1;
		break;
		case DIODE2:
		tempHeater = TEMPERATURE().HEATER2;
		break;
		default:
		break;
	}
	
	if(curDiode == DIODE2) curDiode = DIODE1;
	else curDiode++;

	stopTimerA1;

}