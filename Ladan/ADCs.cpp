#include "ADCs.h"
#include "Uart.h"


float temp;
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
		const float heat = VoltToTemp(ADC_convert(), temp);
		sendTemp("Battery: ", heat);
// 		if(temp > TEMPERATURE().BATTERY)
// 		{	
// 			//BatteryOff;
// 			//HeaterOff;
// 		}
// 		else if(temp < (float)TEMPERATURE().BATTERY - TEMPERATURE().DIFFBATTERY)
// 		{
// 			//BatteryOn;
// 			//HeaterOn;
// 		}
		
	    UARTSend_str("\n\r");
}

void heaterPWR()
{
		const float heat = VoltToTemp(ADC_convert(), temp);
		sendTemp("Heater: ", heat);
		if(heat > (float)(tempHeater))
		{
			HeaterOff;
		}
	
		else if(temp < (float)((tempHeater) - TEMPERATURE().DIFFHEATER)) 
		{
			HeaterOn;
		}
		
		
		UARTSend_str("   ");
}

void power()
{
	temp = ADC_convert();
	sendTemp("Power: ", 1000*Uin(temp));
	
	UARTSend_str("   ");
	
}


ISR (TIMER0_COMPA_vect)
{	
	 ADMUX &= ~(1<<MUX0);
	 ADMUX |= (1<<MUX1);
	 heaterPWR();

	 ADMUX |= (1<<MUX1)|(1<<MUX0);
	 power();
		
	 ADMUX |= (1<<MUX0); 
	 ADMUX &= ~(1<<MUX1);
	 batteryPWR();
	
}