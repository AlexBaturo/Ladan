#include "ADCs.h"

int ADCn = MUX0;
bool flagHeater = true; // true, ����� ���������
bool flagBattery = true;

void iniTimerA0(void)
{
	// ������������� TimerA0

	OCR0A = timeToFloat (TIMER_A0); // ��������� �������� ����������
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
	if(flagBattery)
	{
		if(((ADC_convert ()) >= TEMPERATURE().BATTERY || !pressSensAns)) 
		{	
			BatteryOff;
			flagBattery = false;
		}
	}
	else
	{
		if(((ADC_convert ()) <= TEMPERATURE().BATTERY - DIFF().BATTERY) && pressSensAns)
		{
			BatteryOn;
			flagBattery = true;
		}
		
	}
}

void heaterPWR()
{
	if (flagHeater)
	{
		if(ADC_convert () >= (float)(tempHeater) ) 
		{
			HeaterOff;
			flagHeater = false;
		}
	}
	else
	{
		if(ADC_convert () <= (float)(tempHeater - DIFF().HEATER)) 
		{
			HeaterOn;
			flagHeater = true;
		}
	}
}


ISR (TIMER0_COMPA_vect)
{
	if(ADCn == MUX0)
	{
		ADCn = MUX1;
		heaterPWR();
	}

	else if(ADCn == MUX1)
	{	
		ADCn = MUX0;
		batteryPWR();
	}
}