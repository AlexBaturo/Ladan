#include "ButtonDiods.h"

enum {MODE0, MODE1, MODE2};

float tempHeater;
bool is_sleeping = false;
uint8_t curMode = MODE0;
COLOR_VALUES color_values = COLOR_VALUES();

void iniTimerA1(void)
{
	// инициализация TimerA1

	OCR1A = timeToInt(TIMER_A1); // установка регистра совпадения
	TCCR1B |= (1 << WGM12);  // включить CTC режим
    TIMSK1 |= (1 << OCIE1A);
}


void INT0Enable(bool state)
{
	//Управление прерыванием INT0

	if (state)
	{
		//EICRA |= (1<<ISC01); //включим прерывания INT0 по нисходящему фронту
		EIMSK |= (1<<INT0); //разрешим внешние прерывания INT0
	}
	else
	{
		EIMSK &= ~(1<<INT0);
		//EICRA &= ~(1<<ISC01);
	}
	
}


void initButtonDiodsPins() 
{
	/*Инициализируем выводы для диодов и кнопки,
	  включаем таймерА1 для борьбы с дребезгом,
	  настраиваем внешнее прерывание*/
	  	
	//Диоды 
	diodePortInit;

	//Начальный режим работы
	//HeaterOn;
	
	ButtonPinsInit;
	ButtonPinsOn((1<<BUTTON_PIN2)|(1<<BUTTON_PIN1)|(1<<BUTTON_PIN));

	iniTimerA1();

	startTimerA1;


}



ISR(INT0_vect)
{	
	
	INT0Enable(false);
	diodeOff((1 << DIODE2)|(1 << DIODE1));
	curMode++;
	if(curMode > MODE2) curMode = MODE0;
	is_sleeping = false;


	switch(curMode)
	{
		case MODE0:
		tempHeater = 0;
		break;
		case MODE1:
		tempHeater = TEMPERATURE().HEATER1;
		diodeOn((1 << DIODE1));
		color_values = {255, 0};
		break;
		case MODE2:
		tempHeater = TEMPERATURE().HEATER2;
		diodeOn((1 << DIODE2));
		color_values = {255, 255};
		default:
		break;
	}
	
	startTimerA1;
	
}


ISR(TIMER1_COMPA_vect)
{
	INT0Enable(true);
	stopTimerA1;
	if(curMode == MODE0) is_sleeping = true;

}



