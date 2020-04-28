#include "ButtonDiods.h"

float tempHeater;
uint8_t curDiode;

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
	ButtonPinsOn((1<<BUTTON_PIN2)|(1<<BUTTON_PIN1));

	iniTimerA1();
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


	if(!(ButtonPort & (1<< BUTTON_PIN2)))  curDiode =  DIODE2;
	else if(!(ButtonPort & (1<< BUTTON_PIN1))) curDiode = DIODE1; 


}