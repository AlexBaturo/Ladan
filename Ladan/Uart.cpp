/*
 * Uart.cpp
 *
 * Created: 09.05.2020 20:11:13
 *  Author: 111
 */ 
 #include "Uart.h"


void UARTInit(void) {
	UBRR0H = 0;
	UBRR0L = 6; //baud rate 9600
	UCSR0B = (1<<TXEN0);
	UCSR0C = (1<<UCSZ01)|(1<<UCSZ00); //8 bit, 1 stop bit
}

void UARTSend(uint8_t data)//	Отправка байта
{
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
}

void UARTSend_str(const unsigned char *s)//  Отправка строки
{
	while (*s != 0) UARTSend(*s++);
}
