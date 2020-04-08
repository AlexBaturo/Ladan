#ifndef CONFIG_H_
#define CONFIG_H_

#define diodeOn(x) PORTB |= x 
#define diodeOff(x) PORTB &= ~(x) 
#define diodePortInit(x) DDRB |= x

//�����, ������������ ������
const uint8_t DIODE1 = PB1;
const uint8_t DIODE2 = PB2;
const uint8_t DIODE3 = PB3;

//������ ������� ������ ���
const int TIMERA0 = 200;

//������ ������� ��� ������ �� ��������
const int TIMERA1 = 3000;

//����������� ���������� ���, �
const float	AREF = 5;

//���������� �� �������� �����������, ����
const float DIFF = 0.5;


extern float tempHeater;
extern uint8_t curDiode;



#endif /* CONFIG_H_ */