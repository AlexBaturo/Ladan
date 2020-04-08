#include "ADCs.h"

int ADCn = MUX0;
bool flag = true; // true, ����� ���������

void iniTimerB1(void)
{
	// ������������� TimerB1

	OCR0A = 200; // ��������� �������� ����������
	TCCR0A |= (1<<WGM01); //�������� CTC �����
	TCCR0B |= (1 << CS02);  //��� ����� �� 256
	TIMSK0 |= (1 << OCIE0A);
	
}

void initADC()
{
	DDRD = (1<<PD4)|(1<<PD7);//Test

	ADCSRA |= (1<<ADEN)// ���������� ������������� ���
	|(1<<ADSC)//������ ��������������
	//|(1<<ADATE)//����������� ����� ������ ���
	//|(1<<ADIE)//���������� ����������
	|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);//�������� 128 = 64 ���

	ADMUX |= 0 //AREF, internal Vref turned off
	|(1<<MUX0); // ���� ADC1

	iniTimerB1();
	
}

unsigned int ADC_convert ()
{
	ADCSRA |= (1<<ADSC);
	//�������� ����������� �� ����������
	ADMUX ^= (1<<MUX0);
	ADMUX ^= (1<<MUX1);
	while(ADCSRA & (1<<ADSC))
	{};
	int low_adc = ADCL;
	int high_adc = ADCH;
	return high_adc*256+low_adc;
}

void batteryPWR(double temp)
{
	float n =  (float) ADC_convert ()/208;
	ADCn = MUX0;
	if(n <= temp ) PORTD |= (1<<PD3);
	else PORTD &= ~(1<<PD3);
}

void heaterPWR()
{
	float n =  (float) ADC_convert ()/208;
	ADCn = MUX1;
	float dif = 0.5;
	if (flag)
	{
		if(n < (float)(getTemp() + dif) ) PORTD |= (1<<PD7);
		else
		{
			PORTD &= ~(1<<PD7);
			flag = false;
		}
	}
	else
	{
		if(n > (float)(getTemp() - dif)) PORTD &= ~(1<<PD7);
		else
		{
			PORTD |= (1<<PD7);
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
		batteryPWR(2);
	}
}