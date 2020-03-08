


/*

 * DeadTimeGen_ATtiny45


 *

 * 8MHz internal osc assumed

 */ 

 





#include <avr/io.h>



/*

* Configuration

*/

//set the top count give whole number percentage duty cycles

const unsigned char top = 79;


const unsigned char compare = 39;

//prescale CLK/2, 8Mz clock and div2 prescale -> 4MHz tick -> appropx 50kHz output with top=79

const unsigned char prescaleTimer = (1<<CS11);

//prescale CLK/4.

const unsigned char prescaleDead = (1<<DTPS11);// div 8 = (1<<DTPS11) | (1<<DTPS10)

// with CLK/4 prescale and 8MHz clock the dead time is 0.5uS per LSB.

//Dead time is delay to rising edge of signal

const unsigned char deadHigh = 0x02; //2uS dead time for OCR1B. Max 0x0F

const unsigned char deadLow = 0x02; //2uS dead time for /OCR1B



int main(void)

{

  //set data direction for output compare A and B, incl complements

  DDRB = (1<<PB4) | (1<<PB3) | (1<<PB1) | (1<<PB0);

  

  //setup timer1 with PWM. Will be using both A and B compare outputs.

  // both compares will be the same but only B will have dead time applied

  OCR1A = compare;

  OCR1B = compare;

  TCCR1 = (1<<PWM1A) | (1<<COM1A0); //Compare A PWM mode with complement outputs

  GTCCR = (1<<PWM1B) | (1<<COM1B0); //Compare B PWM mode with complement outputs

  

  //PLLCSR is not set so the PLL will not be used (are using system clock directly - "synchonous mode")

  //OCR1C determines the "top" counter value if CTC1 in TCCR1 is set. Otherwise "top" is normal: 0xFF

  OCR1C = top;

  TCCR1 |= (1<<CTC1);

  TCCR1 |= prescaleTimer; 

  

  //setup dead time for compare B. Note the prescaler is independent of timer1 prescaler (both receive the same clk feed)

  DTPS1 = prescaleDead;

  //DT1A is unset - output A has no dead time

  DT1B = (deadHigh<<4) | deadLow;

  

    while(1)

    {

        //do nothing

    }

}
