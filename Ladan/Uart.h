/*
 * Uart.h
 *
 * Created: 09.05.2020 20:08:17
 *  Author: 111
 */ 


#ifndef UART_H_
#define UART_H_
#include <avr/io.h>
#include <stdio.h>

void UARTInit(void);
void UARTSend(const char data);
void UARTSend_str(const char *s);

#endif /* UART_H_ */