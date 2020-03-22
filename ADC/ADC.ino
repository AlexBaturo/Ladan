 void ADC_Init(void)

{
  // Разрешение использования АЦП
  ADCSRA |= (1<<ADEN);
  //Делитель 128 = 64 кГц
  //|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
  //Внутренний Источник ОН 2,56в, вход ADC3
  ADMUX |= (1<<REFS2)|(1<<REFS1)|(1<<MUX1)|(1<<MUX0);
  
} 

unsigned int ADC_convert (void) 
{
  //Начинаем преобразование
  ADCSRA |= (1<<ADSC); 
  //проверим закончилось ли преобразов
  while((ADCSRA & (1<<ADSC)));  
  return (unsigned int) ADC; 
}


float n; 

void setup() {
  DDRB = (1<<PB4);
  
  ADC_Init();
 

}

void loop() {
 n =  (float) ADC_convert()/310;
 if(n >= 3.1 ) PORTB |= (1<<4);
 else PORTB &= ~(1<<4);

}
