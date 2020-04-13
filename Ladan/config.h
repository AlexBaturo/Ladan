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

#define startTimerA1 TCCR1B |= (1 << CS12);  // ��� ����� �� 256
#define stopTimerA1 TCCR1B &= ~(1 << CS12); \
					TCNT1 = 0;


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

//���  B5761-S 103-F40
/*struct RES_DIV 
{
	//����������� ���������� ���, �
	const static float AREF = 4.92;
	//�������� � ��������, ��
	const static float R = 10000;
	//��������� �� ����
	const static float B = 3988;
	//����������� ��� ���� ���, �
	const static float T0 = 298;
	//������������� �������� ��� ���� ���, ��
	const static float R0 = 10000;

};*/

//��� KTY81/210,112
struct RES_DIV
{
	//����������� ���������� ���, �
	const static float AREF = 4.92;
	//�������� � ��������, ��
	const static float R = 10000;
	//��������� �� ����
	const static float B = -790;
	//����������� ��� ���� ���, �
	const static float T0 = 298;
	//������������� �������� ��� ���� ���, ��
	const static float R0 = 2000;

};


//�������� - �����, ��
float timeToFloat (const float msTime);

//�������� - ����������� � ��������
const float tempToVolt (const float temp);


//���������� �� �������� �����������, ����
struct DIFF
{
	const static float HEATER = 0.0;
	const static float BATTERY = 0.0;
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