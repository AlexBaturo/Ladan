#include "ADCs.h"

int ADCn = MUX0;

void iniTimerB1(void)
{
	// инициализация TimerB1

	OCR0A = 200; // установка регистра совпадения
	TCCR0A |= (1<<WGM01); //включить CTC режим
	TCCR0B |= (1 << CS02);  //уст делит на 256
	TIMSK0 |= (1 << OCIE0A);
	
}
 
 void initADC()
{
  DDRD = (1<<PD4)|(1<<PD7);//Test	

  ADCSRA |= (1<<ADEN)// Разрешение использования АЦП
  |(1<<ADSC)//Запуск преобразования
  //|(1<<ADATE)//Непрерывный режим работы АЦП
  //|(1<<ADIE)//Разрешение прерываний
  |(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);//Делитель 128 = 64 кГц

  ADMUX |= 0 //AREF, internal Vref turned off
  |(1<<MUX0); // вход ADC1

  iniTimerB1();
  
} 

unsigned int ADC_convert () 
{
  ADCSRA |= (1<<ADSC);
  //проверим закончилось ли преобразов
  ADMUX ^= (1<<MUX0);
  ADMUX ^= (1<<MUX1);
  while(ADCSRA & (1<<ADSC))
  {};
  int low_adc = ADCL;
  int high_adc = ADCH;
  return high_adc*256+low_adc;
}

void change(double temp, int mux, int pin)
{
	float n =  (float) ADC_convert ()/208;
	ADCn = mux;
	if(n >= temp ) PORTD |= (1<<pin);
	else PORTD &= ~(1<<pin);
}


ISR (TIMER0_COMPA_vect)
{
	if(ADCn == MUX0)
	{
		change(getTemp(), MUX1, PD7);
	}

	else if(ADCn == MUX1)
	{
		change(2, MUX0, PD3);
	}
}