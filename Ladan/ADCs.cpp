#include "ADCs.h"
#include "Uart.h"


float temp;
bool batteryFlag = true;
bool voltage = true;


void iniTimerA0(void)
{
	//таймер для опроса АЦП TimerA0

	OCR0A = 255; // частота таймера
	TCCR0A |= (1<<WGM01); //выбор режима CTС
	TCCR0B |= (1 << CS02)|(1 << CS00);  //делитель 256
	TIMSK0 |= (1 << OCIE0A);
	
}

void resetTimerA0(void)
{
	OCR0A = 0;
	TCCR0A &= ~(1<<WGM01); //выбор режима CTС
	TCCR0B &= ~((1 << CS02)|(1 << CS00));  //делитель 256
	TIMSK0 &= ~(1 << OCIE0A);
}

void initADC()
{
	//инициальизация портов
	termoPortInit;

	DDRC |= (1<<PC4);
	PORTC |= (1<<PC4);

	DDRC |= (1<<PC0);
	PORTC |= (1<<PC0);

	ADCSRA |= (1<<ADEN)// разрешаем работу АЦП
	|(1<<ADSC)//инициализируем работу АЦП
	|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);//частота работы ацп
	
	ADMUX |= (1<<REFS1)|(1<<REFS0);
// 	ADMUX |= 0 //AREF, internal Vref turned off
// 	|(1<<MUX0); // работает ADC1

	iniTimerA0();
	
}

void resetAdc()
{
	ADCSRA =0;
	ADMUX = 0;

	DDRC &= ~((1<<PC4)|(1<<PC0));
	PORTC &= ~((1<<PC4)|(1<<PC0));

	resetTimerA0();
}

float ADC_convert ()
{
	int low_adc;
	int high_adc;

	//переключаем АЦП
	for(int i = 0; i<3 ; i++)
	{
		ADCSRA |= (1<<ADSC);
		while(ADCSRA & (1<<ADSC))
		{};

		low_adc = ADCL;
		high_adc = ADCH;
	}
	return RES_DIV().AREF*(high_adc*256+low_adc)/1024;
}

void sendTemp(char *name, const float temp)
{
	char str[3];
	sprintf(str, "%d", (int)temp);
	UARTSend_str(name);
	UARTSend_str(str);
	UARTSend_str("    ");
}

void batteryPWR()
{		
		const float heat = VoltToTemp1(ADC_convert(), temp);
		sendTemp("Battery: ", heat);
		if(heat > TEMPERATURE().BATTERY)
		{	
			batteryFlag = false;
		}
		else if(heat < (float)(TEMPERATURE().BATTERY - TEMPERATURE().DIFFBATTERY))
		{
			batteryFlag = true;
		}
		
	    UARTSend_str("   ");
}

void heaterPWR()
{
		const float heat = VoltToTemp(ADC_convert(), temp);
		sendTemp("Heater: ", heat);
		if(heat > (float)(tempHeater) || !batteryFlag )
		{
			HeaterOff;
		}
	
		else if((heat < (float)(tempHeater - TEMPERATURE().DIFFHEATER)) && batteryFlag) 
		{
			HeaterOn;
		}
		
		
		UARTSend_str("   ");
}

void power()
{
	temp = ADC_convert();
	const float pwr = Uin(temp);
	sendTemp("Power: ", 1000*pwr);
	sendTemp("Power: ", Uin(temp));


	if(pwr < 3.2)
	{
		PORTD &= ~((1<<PD6)|(1<<PD5));
		resetAdc();
		voltage = false;
		for(int i=0; i<2; i++)
		{
			PORTD |= (1<<PD6);
			for(long int j =0; j < 300000; j++){};
			PORTD &= ~(1<<PD6);
			for(long int j =0; j < 300000; j++){}
		}
		is_sleeping = true;
	}
	else voltage = true;
	UARTSend_str("\n\r");
	
}


ISR (TIMER0_COMPA_vect)
{	
	wdt_reset();	
	ADMUX |= (1<<MUX1)|(1<<MUX0);
	ADMUX &=~(1<<MUX2);
	power();

	if (voltage)
	{
		ADMUX |= (1<<MUX2)|(1<<MUX1)|(1<<MUX0);
		batteryPWR();
		
		ADMUX &=~(1<<MUX2);
		ADMUX &= ~(1<<MUX0);
		ADMUX |= (1<<MUX1);
		heaterPWR();
	}
	 
	
}