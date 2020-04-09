#include "ADCs.h"

int ADCn = MUX0;
bool flag = true; // true, ����� ���������


void iniTimerA0(void)
{
	// ������������� TimerA0

	OCR0A = TIMER_A0; // ��������� �������� ����������
	TCCR0A |= (1<<WGM01); //�������� CTC �����
	TCCR0B |= (1 << CS02);  //��� ����� �� 256
	TIMSK0 |= (1 << OCIE0A);
	
}

void initADC()
{
	//�������������� ����� � ��������� �����������
	termoPortInit;
	pressSensInit;

	ADCSRA |= (1<<ADEN)// ���������� ������������� ���
	|(1<<ADSC)//������ ��������������
	//|(1<<ADATE)//����������� ����� ������ ���
	//|(1<<ADIE)//���������� ����������
	|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);//�������� 128 = 64 ���

	ADMUX |= 0 //AREF, internal Vref turned off
	|(1<<MUX0); // ���� ADC1

	iniTimerA0();
	
}

float ADC_convert ()
{
	ADCSRA |= (1<<ADSC);
	//�������� ����������� �� ����������
	ADMUX ^= (1<<MUX0);
	ADMUX ^= (1<<MUX1);
	while(ADCSRA & (1<<ADSC))
	{};
	int low_adc = ADCL;
	int high_adc = ADCH;
	return AREF*(high_adc*256+low_adc)/1024;
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