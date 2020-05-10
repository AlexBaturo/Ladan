#include "ButtonDiods.h"

float tempHeater;
enum {MODE0, MODE1, MODE2};
uint8_t curMode = MODE0;

void iniTimerA1(void)
{
	// инициализация TimerA1

	OCR1A = timeToInt(TIMER_A1); // установка регистра совпадения
	TCCR1B |= (1 << WGM12);  // включить CTC режим
	TIMSK1 |= (1 << OCIE1A);
	
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




ISR (TIMER1_COMPA_vect)
{	
	
	
	switch(curMode)
	{
		case MODE0:
		tempHeater = 0;
		break;
		case MODE1:
		tempHeater = TEMPERATURE().HEATER1;
		diodeOn((1 << DIODE1));
		break;
		case MODE2:
		tempHeater = TEMPERATURE().HEATER2;
		diodeOn((1 << DIODE2));
		default:
		break;
	}


	if(!(ButtonPort & (1<< BUTTON_PIN))) 
	{
		curMode++;

		while (!(ButtonPort & (1<< BUTTON_PIN))){};
		diodeOff((1 << DIODE2)|(1 << DIODE1));
	}
	if(curMode > MODE2) curMode = MODE0;


}