/* Defines -----------------------------------------------------------*/

// pins for rotary encoder
#define EN_DT PB3     // PB3 is where the DT pin of the encoder is connected
#define EN_CLK PB4    // PB4 is where the CLK pin of the encoder is connected
#define EN_SW PB5     // PB5 is an AVR pin where the button of the encoder is connected

#define servo1 PB1    // PWM od the Servo1 connection
#define servo2 PB2    // PWM od the Servo2 connection

# define min_pos 1000   // the minimum position to which the servo will turn
# define max_pos 2500   // the maximum position to which the servo will turn
# define step 500
# define DELAY 1000   // Delay in milliseconds


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

uint32_t m1_position = min_pos;
uint32_t m2_position = min_pos;

int main(void)
{
  GPIO_mode_input_pullup(&DDRB,EN_SW);
  GPIO_mode_input_pullup(&DDRB,EN_DT);
  GPIO_mode_input_pullup(&DDRB,EN_CLK);

  GPIO_mode_output(&DDRB, servo1);
  GPIO_mode_output(&DDRB, servo2);

  TIM0_overflow_interrupt_enable();
  TIM0_overflow_16ms();


  //Working with registers to rotate the servos, mode 8 (1000)
  TCCR1B |= (1<<WGM13);

  TCCR1A |= (1<<COM0A1) | (1<<COM0B1);        // set compare output mode

  ICR1 = 20000;

  OCR1A = m1_position;
  OCR1B = m2_position;

  TCCR1B |= (1<<CS11);            // set prescaler to 8

  PCICR |= (1<<PCIE0);            // Any change of any enable PCINT[7:0] pins will cause an interrupt
  PCMSK0 |= (1<<PCINT0);          // Enable PCINT0 change interrupt  
  

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
        if (cnt_en == 1)      // if button 0, work with servo 1
        {
          m1_position += step;     

          if (m1_position == max_pos)
          {
            m1_position = min_pos;
          }
               
        }
    
        else if (cnt_en == 0)
        {
          m2_position += step;     

          if (m2_position == max_pos)
          {
            m2_position = min_pos;
          }
        }
       
      }
        
      else
      {  
        if (cnt_en == 1)      
        {
        }
    
        else if (cnt_en == 0)
        {
        }
      }
      OCR1A = m1_position;
      OCR1B = m2_position;
    }
  }
  ls_en_r = cs_en_r;
}
