#include "ADCs.h"

int ADCn = MUX0;


void iniTimerA0(void)
{
	//таймер для опроса АЦП TimerA0

	OCR0A = timeToInt (TIMER_A0); // частота таймера
	TCCR0A |= (1<<WGM01); //выбор режима CTС
	TCCR0B |= (1 << CS02)|(1 << CS00);  //делитель 256
	TIMSK0 |= (1 << OCIE0A);
	
}

void initADC()
{
	//инициальизация портов
	termoPortInit;
	pressSensInit;

	ADCSRA |= (1<<ADEN)// разрешаем работу АЦП
	|(1<<ADSC)//инициализируем работу АЦП
	|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);//частота работы ацп

	ADMUX |= 0 //AREF, internal Vref turned off
	|(1<<MUX0); // работает ADC1

	iniTimerA0();
	
}

float ADC_convert ()
{
	ADCSRA |= (1<<ADSC);
	//переключаем АЦП
	
	while(ADCSRA & (1<<ADSC))
	{};
	int low_adc = ADCL;
	int high_adc = ADCH;
	return RES_DIV().AREF*(high_adc*256+low_adc)/1024;
}

void batteryPWR()
{
		if(((ADC_convert ()) > TEMPERATURE().BATTERY || !pressSensAns)) 
		{	
			BatteryOff;
		}
		else if(((ADC_convert ()) < TEMPERATURE().BATTERY ) && pressSensAns)
		{
			BatteryOn;
		}
		
	
}

void heaterPWR()
{
	
		if(ADC_convert () > (float)(tempHeater) ) 
		{
			HeaterOff;
		}
	
		else if(ADC_convert () < (float)(tempHeater - 0.01)) 
		{
			HeaterOn;
		}
	
}


ISR (TIMER0_COMPA_vect)
{
	ADMUX |= (1<<MUX0);
	ADMUX &= ~(1<<MUX1);
	heaterPWR();
	
	ADMUX |= (1<<MUX1);
	ADMUX &= ~(1<<MUX0);
	batteryPWR();
	
}