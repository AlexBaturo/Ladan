#include "ADCs.h"

int ADCn = MUX0;
bool flag = true; // true, когда нагреваем


void iniTimerA0(void)
{
	// инициализация TimerA0

	OCR0A = TIMER_A0; // установка регистра совпадения
	TCCR0A |= (1<<WGM01); //включить CTC режим
	TCCR0B |= (1 << CS02);  //уст делит на 256
	TIMSK0 |= (1 << OCIE0A);
	
}

void initADC()
{
	//Инициализируем порты с датчиками температуры
	termoSensorsPortInit;

	ADCSRA |= (1<<ADEN)// Разрешение использования АЦП
	|(1<<ADSC)//Запуск преобразования
	//|(1<<ADATE)//Непрерывный режим работы АЦП
	//|(1<<ADIE)//Разрешение прерываний
	|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);//Делитель 128 = 64 кГц

	ADMUX |= 0 //AREF, internal Vref turned off
	|(1<<MUX0); // вход ADC1

	iniTimerA0();
	
}

float ADC_convert ()
{
	ADCSRA |= (1<<ADSC);
	//проверим закончилось ли преобразов
	ADMUX ^= (1<<MUX0);
	ADMUX ^= (1<<MUX1);
	while(ADCSRA & (1<<ADSC))
	{};
	int low_adc = ADCL;
	int high_adc = ADCH;
	return (high_adc*256+low_adc)/DIV_ADC;
}

void batteryPWR()
{
	ADCn = MUX0;
	if((ADC_convert ()) <= TEMP_BATTERY ) tSensorBatteryOn;
	else tSensorBatteryOff;
}

void heaterPWR()
{
	ADCn = MUX1;
	if (flag)
	{
		if(ADC_convert () < (float)(tempHeater + DIFF) ) 
		{
			tSensorHeaterOn;
		}
		else
		{
			tSensorHeaterOff;
			flag = false;
		}
	}
	else
	{
		if(ADC_convert () > (float)(tempHeater - DIFF)) 
		{
			tSensorHeaterOff;
		}
		else
		{
			tSensorHeaterOn;
			flag = true;
		}
	}
}


ISR (TIMER0_COMPA_vect)
{
	if(ADCn == MUX0)
	{
		heaterPWR();
	}

	else if(ADCn == MUX1)
	{
		batteryPWR();
	}
}