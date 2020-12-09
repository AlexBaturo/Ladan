#include "ButtonDiods.h"
#include "Uart.h"
#include "PWM.h"


enum {MODE0, MODE1, MODE2, MODE3};

float tempHeater;
bool isFirst;
uint32_t red;
uint32_t green;

bool is_sleeping = true;
uint8_t curMode = MODE1;
pwmPinsManage pwm = pwmPinsManage(RED, GREEN);


void PCINTEnable(bool state)
{
	//Управление прерыванием INT0

	if (state)
	{

		PCMSK2 |= (1<<PCINT18);
		// Enable pin change interrupt 2 using the Pin Change Interrrupt Control Register (PCICR)
		PCICR |= (1<<PCIE2);
	}
	else
	{
		PCMSK2 &= ~(1<<PCINT18);
		PCICR &= ~(1<<PCIE2);
	}
	
}




class Bounce
{
public:
	bool counter()
		{	
			PCINTEnable(false);
			while(count < 10000)
			{
				count++;	
			}
			count = 0;
			PCINTEnable(true);
			return !(PIND & (1<<PD2));
		}
private:
	unsigned int count = 0;
};




void initButtonDiodsPins() 
{
	/*Инициализируем выводы для диодов и кнопки,
	  включаем таймерА1 для борьбы с дребезгом,
	  настраиваем внешнее прерывание*/
	  	

	//Начальный режим работы
	//HeaterOn;
	
	ButtonPinsOn;

	PCINTEnable(true);

}

Bounce bounce = Bounce();


ISR(PCINT2_vect)
{	
	
	//wdt_enable(WDTO_4S);
	if(bounce.counter())
		{
			unsigned count = 0;
			while(!(PIND & (1<<PD2)))
				{	
					wdt_reset();
					if(count++ > TIME_BEFORE_ON) 
						{	
							if(is_sleeping) 
								{
									is_sleeping = false;
									isFirst = true;
									curMode = MODE1;
									initADC();
									pwm.launchPwm(0, 0);
									//PORTD |= (1<<HEATER);
									
								}
							else
								{
									//DDRD &= ~(1<<HEATER);
									PORTD &= ~(1<<HEATER);
									is_sleeping = true;
									pwm.launchPwm(0, 0);
									resetAdc();
									//wdt_disable();
									tempHeater = TEMPERATURE().HEATER_OFF;
								} 
							break;
						}

 					char str[3];
 					sprintf(str, "%d", (int)count);
 					UARTSend_str(str);
 					UARTSend_str("\n\r");
				}
	
			if(!is_sleeping )
				{
					
					if(curMode > MODE3) curMode = MODE1;
					switch(curMode)
						{
							case MODE1:
							tempHeater = TEMPERATURE().HEATER1;
	     					pwm.launchPwm(50, 255);
							break;
							case MODE2:
							tempHeater = TEMPERATURE().HEATER2;
 							pwm.launchPwm(255, 0);	
							break;
							case MODE3:
							tempHeater = TEMPERATURE().HEATER_SAFETY;
							pwm.launchPwm(0, 255);
							break;	
							default:
							break;
						}
						curMode++;
					}
			}
	
}




