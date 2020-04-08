#ifndef CONFIG_H_
#define CONFIG_H_

#define diodeOn(x) PORTB |= x 
#define diodeOff(x) PORTB &= ~(x) 
#define diodePortInit DDRB |= (1 << DIODE2)|(1 << DIODE1)
#define termoSensorsPortInit DDRD |= (1<<BATTERY)|(1<<HEATER)
#define tSensorHeaterOn PORTD |= (1<<HEATER)
#define tSensorHeaterOff PORTD &= ~(1<<HEATER)
#define tSensorBatteryOn PORTD |= (1<<BATTERY)
#define tSensorBatteryOff PORTD &= ~(1<<BATTERY)

//���������� �������������
const uint8_t HEATER = PD7;
const uint8_t BATTERY = PD3; 

//�����, ������������ ������
const uint8_t DIODE1 = PB1;
const uint8_t DIODE2 = PB2;


//������ ������� ������ ���
const int TIMER_A0 = 200;

//������ ������� ��� ������ �� ��������
const int TIMER_A1 = 3000;

//����������� ���������� ���, �
const float	AREF = 5;

//���������� �� �������� �����������, ����
const float DIFF = 0.5;

//������������ ����������� �������, ����
const float TEMP_BATTERY = 2;

//�������� ��������� �������� � ���,
//����� ������� �������� ���������� �� 0 �� AREF
const float DIV_ADC = 1024/AREF;


struct MODE 
{
	//���������� ��� ����������� 80, �
	const static float MODE1 = 1;
	//���������� ��� ����������� 130, �
	const static float MODE2 = 2;	
};



extern float tempHeater;
extern uint8_t curDiode;



#endif /* CONFIG_H_ */