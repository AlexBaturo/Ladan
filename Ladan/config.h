#ifndef CONFIG_H_
#define CONFIG_H_

#include <avr/io.h>

#define F_CPU 1000000UL
#define diodeOn(x) PORTB |= x 
#define diodeOff(x) PORTB &= ~(x) 
#define diodePortInit DDRB |= (1 << DIODE2)|(1 << DIODE1)
#define termoPortInit DDRD |= (1<<BATTERY)|(1<<HEATER)
#define HeaterOn PORTD |= (1<<HEATER)
#define HeaterOff PORTD &= ~(1<<HEATER)
#define BatteryOn PORTD |= (1<<BATTERY)
#define BatteryOff PORTD &= ~(1<<BATTERY)
#define pressSensInit DDRB &= ~(1<<PRESSURE); \
					  PORTB |= (1<<PRESSURE);
#define pressSensAns !(PINB & (1<<PRESSURE))

//���������� �������������
const uint8_t HEATER = PD7;
const uint8_t BATTERY = PD3; 

//�����, ������������ ������
const uint8_t DIODE1 = PB1;
const uint8_t DIODE2 = PB2;

//�����, ���� ��������� �������� �������������
const uint8_t PRESSURE = PB6;

//������ ������� ������ ���, ��
const int TIMER_A0 = 300;

/*������ ������� ��� ������ �� ��������, 
	���������� ����� 1000 ��  */
const int TIMER_A1 = 1000;

//����������� ���������� ���, �
const static float	AREF = 5;


//���������� �� �������� �����������, ����
struct DIFF
{
	const static float HEATER = 0.5;
	const static float BATTERY = 0.5;
};


//������ ������
struct TEMPERATURE 
{
	//���������� ��� ����������� 80, �
	const static float HEATER1 = 1;
	//���������� ��� ����������� 130, �
	const static float HEATER2 = 2;	
	//������������ ����������� �������, ����
	const static float BATTERY = 2;
};

//�������� �������
const int TIMER_DIVIDER = 256;

extern float tempHeater;
extern uint8_t curDiode;


float timeToFloat (float msTime);



#endif /* CONFIG_H_ */