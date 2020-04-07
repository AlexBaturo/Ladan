#include "ButtonDiods.h"

unsigned int cur = PB1;
int temp = 1;

void iniTimerA1(void)
{
	// инициализация TimerA1

	OCR1A = 3000; // установка регистра совпадения
	TCCR1B |= (1 << WGM12)|(1 << CS12);;  // включить CTC режим, уст делит на 256
	TIMSK1 |= (1 << OCIE1A);
	
}

void INT0Enable(bool state)
{
	//Управление прерыванием INT0

	if (state)
	{
		EICRA |= (1<<ISC01); //включим прерывания INT0 по нисходящему фронту
		EIMSK |= (1<<INT0); //разрешим внешние прерывания INT0
	}
	else
	{
		EIMSK &= ~(1<<INT0);
		EICRA &= ~(1<<ISC01);
	}
	
}

void initButtonDiodsPins() 
{
	/*Инициализируем выводы для диодов и кнопки,
	  включаем таймерА1 для борьбы с дребезгом,
	  настраиваем внешнее прерывание*/
	  	
	//Диоды 
	DDRD |= (1<<PB3)|(1<<PB2)|(1<<PB1);

	PORTB |=  (1 << PB1);
	
	//Включим ножку INT0 на вход
	DDRD &= ~(1<<PD2);
	
	//Подтянем резистор на ножке INT0 к питанию
	PORTD |= (1<<PD2);

	iniTimerA1();
}

int getTemp()
{
	return temp;
}


ISR(INT0_vect)
{
	INT0Enable(false);
	PORTB &= ~((1 << PB3)|(1<<PB2)|(1<<PB1));
	PORTB |=  (1 << cur);
	
	switch(cur)
	{
		case PB1:
			temp = 1;
			break;
		case PB2:
			temp = 2;
			break;
		case PB3:
			temp = 3;
			break;
		default:
			break;
	}
	
	 
	if(cur == PB3) cur = PB1;
	else cur++;
}

ISR (TIMER1_COMPA_vect)
{
	INT0Enable(true);
}