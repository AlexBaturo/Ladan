#include "ADCs.h"
#include "Uart.h"
#include <stdio.h>

int ADCn = MUX0;


void iniTimerA0(void)
{
	//таймер для опроса АЦП TimerA0

	OCR0A = 255; // частота таймера
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

void sendTemp(char *name, const float volt)
{
	char str[3];
	sprintf(str, "%d", (int)VoltToTemp(volt));
	UARTSend_str(name);
	UARTSend_str(str);
	UARTSend_str("    ");
}

void batteryPWR()
{		
		const float volt  = ADC_convert();
		sendTemp("Battery: ", volt);
		if((volt) > TEMPFUNC().BATTERY)
		{	
			//BatteryOff;
			HeaterOff;
		}
		else if(((volt) < (float)(TEMPFUNC().MINBATTERY) ))
		{
			//BatteryOn;
			HeaterOn;
		}
		
	    UARTSend_str("\n\r");
}

void heaterPWR()
{
		const float volt  = ADC_convert();
		sendTemp("Heater: ", volt);
		if(volt > (float)(tempHeater) ) 
		{
			HeaterOff;
		}
	
		else if(volt < (float)(tempDiff)) 
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