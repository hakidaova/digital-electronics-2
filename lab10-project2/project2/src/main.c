/* Defines -----------------------------------------------------------*/

// pins for rotary encoder
#define EN_SW PB2   // PB2 is an AVR pin where the button of the encoder is connected
#define EN_DT PB3   // PB3 is where the DT pin of the encoder is connected
#define EN_CLK PB4  // PB4 is where the CLK pin of the encoder is connected

#define PWM1 PD5 // PWM od the Servo1 connection
#define PWM2 PD6 // PWM od the Servo2 connection

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <util/delay.h>     // Functions for busy-wait delay loops
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include <gpio.h>           // GPIO library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include <stdlib.h>         // C library. Needed for number conversions¨

uint8_t ls_en, cs_en;             // last state, current state of encoder button
uint8_t ls_en_r, cs_en_r;         // last state, current state of the rotary encoder             
int8_t cnt_en = 0;
int8_t cnt_en_r = 0;


int main(void)
{
  GPIO_mode_input_pullup(&DDRB,EN_SW);
  GPIO_mode_input_pullup(&DDRB,EN_DT);
  GPIO_mode_input_pullup(&DDRB,EN_CLK);

  TIM0_overflow_interrupt_enable();
  TIM0_overflow_1ms();

  //Working with registers to rotate the servos, mode 5 (101), prescaler 8
  DDRD |= (1<<PD5);
  DDRD |= (1<<PD6);
  OCR0A = 200;
  TCCR0A |= (1<<COM0A1) | (1<<COM0B1) | (1<<WGM00);

  TCCR0B |= (1<<CS01) | (1<<WGM02);





  //Working with registers to rotate the servos, mode 8 (1000)
 // TCCR1A |= (1<<WGM13);

  //TCCR1A |= (1<<COM1A1) | (1<<COM1B1);

  //ICR1 = 2500;





  // Enables interrupts by setting the global interrupt mask
    sei();

    // Infinite loop
    while (1)
    {
        /* Empty loop. All subsequent operations are performed exclusively 
         * inside interrupt service routines, ISRs */
    }

    // Will never reach this
    return 0;
}

ISR(TIMER0_OVF_vect)
{
  // reading the state of the button on encoder
  
  /***************************************************************** 
  * With the change of the state from 1 to 0, one servo is started 
  * and with the change from 0 to 1 we stop that servo and start 
  * the other one
  ******************************************************************/

  //working with the button of the rotary encoder
  cs_en = GPIO_read(&PINB,EN_SW);
    if (cs_en!=ls_en)
    {
      if (GPIO_read(&PINB,EN_SW)==cs_en && cs_en==1)
      {
        if(cnt_en==0)
        {
          cnt_en++;
        }
        else
        {
          cnt_en--;
        }
      }
    }
  ls_en=cs_en;

  //working with the rotary encoder
  cs_en_r = GPIO_read(&PINB, EN_CLK);
    if (cs_en_r != ls_en_r && cs_en_r == 1)
    {
      if(GPIO_read(&PINB, EN_DT) != cs_en_r) //rotating clockwise
      {
        if(cnt_en_r==0)
        {
          cnt_en_r++;
        }
        else
        {
          cnt_en_r--;
        }
      }
    }
    ls_en_r = cs_en_r;
}
