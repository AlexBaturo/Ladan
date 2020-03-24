unsigned int adc_value;
int high_adc=0,low_adc=0; 
 
 void ADC_Init(void)

{
  // Разрешение использования АЦП
  ADCSRA |= (1<<ADEN)// Разрешение использования АЦП
  |(1<<ADSC)//Запуск преобразования
  |(1<<ADATE)//Непрерывный режим работы АЦП
  |(1<<ADIE)//Разрешение прерываний
  |(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);//Делитель 128 = 64 кГц
  ADMUX |= (1<<REFS2)|(1<<REFS1)|(1<<REFS0)//Внутренний Источник ОН 2,56в и Vref PB0
  |(1<<MUX1)|(1<<MUX0); // вход ADC3

  
} 

/*unsigned int ADC_convert (void) 
{
  //Начинаем преобразование
  ADCSRA |= (1<<ADSC); 
  //проверим закончилось ли преобразов
  while((ADCSRA & (1<<ADSC)));  
  return (unsigned int) ADC; 
}*/


float n; 

void setup() {
  DDRB = (1<<PB4);
  
  ADC_Init();
 

}

void loop() {
 n =  (float) adc_value/416;
 if(n >= 1.76 ) PORTB |= (1<<4);
 else PORTB &= ~(1<<4);

}


ISR(ADC_vect)

{
  low_adc = ADCL;
  high_adc = ADCH;
  adc_value = high_adc*256+low_adc;
}
