/* Defines -----------------------------------------------------------*/

// pins for rotary encoder
#define EN_DT PB3       // PB3 is where the DT pin of the encoder is connected
#define EN_CLK PB4      // PB4 is where the CLK pin of the encoder is connected
#define EN_SW PB5       // PB5 is an AVR pin where the button of the encoder is connected

#define servo1 PB1      // PWM od the Servo1 connection
#define servo2 PB2      // PWM od the Servo2 connection

# define min_pos 950    // The minimum position to which the servo will turn
# define max_pos 2050   // The maximum position to which the servo will turn
# define step 50        // Step with which the servo motors rotates
# define DELAY 1000     // Delay in milliseconds


/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <util/delay.h>     // Functions for busy-wait delay loops
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include <gpio.h>           // GPIO library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include <stdlib.h>         // C library. Needed for number conversions¨

uint8_t ls_en, cs_en;             // Last state, current state of encoder button
uint8_t ls_en_r, cs_en_r;         // Last state, current state of the rotary encoder             
int8_t cnt_en = 0;
int8_t cnt_en_r = 0;

// Starting positions of servo motors
uint32_t m1_position = min_pos;   
uint32_t m2_position = max_pos;


int main(void)
{
  // Set pins for encoder 
  GPIO_mode_input_pullup(&DDRB,EN_SW);
  GPIO_mode_input_pullup(&DDRB,EN_DT);
  GPIO_mode_input_pullup(&DDRB,EN_CLK);

  // Set pins for servo motors as outputs
  GPIO_mode_output(&DDRB, servo1);
  GPIO_mode_output(&DDRB, servo2);

  // Configure Timer/Counter 0
  // Enable the interrupt and set the overflow prescaler to 16 ms  
  TIM0_overflow_interrupt_enable();
  TIM0_overflow_16ms();

  // Waveform Generation Mode 8 (1000)
  TCCR1B |= (1<<WGM13);

  // Set compare output mode
  TCCR1A |= (1<<COM0A1) | (1<<COM0B1);

  // Set TOP value 
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


/* Interrupt service routines ----------------------------------------*/
/**********************************************************************
 * Function: Timer/Counter0 overflow interrupt
 **********************************************************************/


ISR(TIMER0_OVF_vect)
{

  /*******************************************************************
  * Reading the state of the button on encoder with the change of the state from 1 to 0 and conversely
  ********************************************************************/

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


  /*******************************************************************
   * Working with the rotary encoder
   * When rotating the encoder clockwise, the servo 1 is rotating clockwise,
   * after pressing the button, the servo 2 rotating counterclockwise when
   * rotating the encoder counterclockwise.
   ******************************************************************/

  cs_en_r = GPIO_read(&PINB, EN_CLK);
  if (cs_en_r != ls_en_r && cs_en_r == 1)
  {
    if(GPIO_read(&PINB, EN_DT) != cs_en_r)    // Rotate the encoder clockwise
    {            
      if (cnt_en == 1)      // Value 1 after pressing the button
      {
        m1_position += step;    

        // If servo 1 reaches the maximum position, turn it back
        if (m1_position == max_pos)
        {
          m1_position = min_pos;
        }               
      }      
    }   

    else      // Rotate the encoder counterclockwise
    { 
      if (cnt_en == 0)      // Value 0 after pressing the button
      {
        m2_position -= step;     

        // If servo 2 reaches the minimum position, turn it back
        if (m2_position == min_pos)   
        {
          m2_position = max_pos;  
        }
      }
    }

    // Put servo values to registers
    OCR1A = m1_position;
    OCR1B = m2_position;
    
  }
  ls_en_r = cs_en_r;
}
