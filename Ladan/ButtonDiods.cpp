#include "ButtonDiods.h"
#include "Uart.h"


enum {MODE0, MODE1, MODE2};

float tempHeater;
bool is_sleeping = true;
uint8_t curMode = MODE1;
COLOR_VALUES color_values = COLOR_VALUES();


void PCINTEnable(bool state)
{
	//Управление прерыванием INT0

	if (state)
	{
		//EICRA |= (1<<ISC01); //включим прерывания INT0 по нисходящему фронту
		//EIMSK |= (1<<INT0); //разрешим внешние прерывания INT0
		PCMSK2 |= (1<<PCINT18);

		// Enable pin change interrupt 2 using the Pin Change Interrrupt Control Register (PCICR)
		PCICR |= (1<<PCIE2);
	}
	else
	{
		//EIMSK &= ~(1<<INT0);
		//EICRA &= ~(1<<ISC01);
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
void iniTimerA1(void)
{
	// инициализация TimerA1

	//OCR1A = timeToInt(TIMER_A1); // установка регистра совпадения
	OCR1A = 5000;
	TCCR1B |= (1 << WGM12);  // включить CTC режим
    TIMSK1 |= (1 << OCIE1A);
}




void initButtonDiodsPins() 
{
	/*Инициализируем выводы для диодов и кнопки,
	  включаем таймерА1 для борьбы с дребезгом,
	  настраиваем внешнее прерывание*/
	  	
	//Диоды 
	diodePortInit;

	//Начальный режим работы
	//HeaterOn;
	
	ButtonPinsInit;
	ButtonPinsOn((1<<BUTTON_PIN2)|(1<<BUTTON_PIN1)|(1<<BUTTON_PIN));

	PCINTEnable(true);

}

Bounce bounce = Bounce();

ISR(PCINT2_vect)
{	
	
	//is_sleeping = false;
	//wdt_enable(WDTO_4S);
	DDRD |= (1<<HEATER);
	
	if(bounce.counter())
		{
			unsigned count = 0;
			while(!(PIND & (1<<PD2)))
				{	
					if(count++ > 300) 
						{
							diodeOff((1 << DIODE1)|(1<<DIODE2));
							if(is_sleeping) 
								{
									is_sleeping = false;
									PORTD |= (1<<HEATER);
									
								}
							else
								{
									//DDRD &= ~(1<<HEATER);
									PORTD &= ~(1<<HEATER);
									is_sleeping = true;
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
					diodeOff((1 << DIODE1)|(1<<DIODE2));
					curMode++;
					if(curMode > MODE2) curMode = MODE1;
					switch(curMode)
						{
							case MODE1:
							tempHeater = TEMPERATURE().HEATER1;
							diodeOn((1 << DIODE1));
							color_values = {255, 0};
							break;
							case MODE2:
							tempHeater = TEMPERATURE().HEATER2;
							diodeOn((1 << DIODE2));
							color_values = {0, 255};
							default:
							break;
						}
					}
			}
	
}


// ISR(TIMER1_COMPA_vect)
// {
// 	INT0Enable(true);
// 	stopTimerA1;
// }



