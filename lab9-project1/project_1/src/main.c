/***********************************************************************
 * 
 * Stopwatch by Timer/Counter2 on the Liquid Crystal Display (LCD)
 *
 * ATmega328P (Arduino Uno), 16 MHz, PlatformIO
 *
 * Copyright (c) 2017 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 * Components:
 *   16x2 character LCD with parallel interface
 *     VSS  - GND (Power supply ground)
 *     VDD  - +5V (Positive power supply)
 *     Vo   - (Contrast)
 *     RS   - PB0 (Register Select: High for Data transfer, Low for Instruction transfer)
 *     RW   - GND (Read/Write signal: High for Read mode, Low for Write mode)
 *     E    - PB1 (Read/Write Enable: High for Read, falling edge writes data to LCD)
 *     D3:0 - NC (Data bits 3..0, Not Connected)
 *     D4   - PD4 (Data bit 4)
 *     D5   - PD5 (Data bit 5)
 *     D6   - PD6 (Data bit 3)
 *     D7   - PD7 (Data bit 2)
 *     A+K  - Back-light enabled/disabled by PB2
 * 
 **********************************************************************/

/* Defines -----------------------------------------------------------*/
// pins for joystick
#define JS_SW PD2   // PD2 is an AVR pin where the button of the joystick is connected
#define JS_VRx PC0  // PC0 is where the VRx pin of the joystick is connected
#define JS_VRy PC1  // PC1 is where the VRy pin of the joystick is connected

// pins for LED
#define LED_RED PC5 // PC5 is where the LED diode is connected

// pins for rotary encoder
#define EN_SW PB2   // PB2 is an AVR pin where the button of the encoder is connected
#define EN_DT PB3   // PB3 is where the DT pin of the encoder is connected
#define EN_CLK PB4  // PB4 is where the CLK pin of the encoder is connected

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include <gpio.h>           // GPIO library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include <lcd.h>            // Peter Fleury's LCD library
#include <stdlib.h>         // C library. Needed for number conversions

// -----
// This part is needed to use Arduino functions but also physical pin names.
#include "Arduino.h"
#define PC5 19              // In Arduino world, PC5 is called "19"



/*----- Define global variables -----*/

uint16_t x, y;                    // coordinates x, y
uint8_t ls_js, cs_js;             // last state, current state of joystick button
uint8_t ls_en, cs_en;             // last state, current state of encoder button
uint8_t ls_en_r, cs_en_r;         // last state, current state of the rotary encoder
int8_t cnt_js = 0;                
int8_t cnt_en = 0;
int8_t cnt_en_r = 0;




/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:  Update stopwatch value on LCD screen when 8-bit 
 *           Timer/Counter2 overflows.
 * Returns:  none
 **********************************************************************/
int main(void)
{
    GPIO_mode_input_pullup(&DDRD,JS_SW); 
    
    GPIO_mode_input_pullup(&DDRB,EN_SW);
    GPIO_mode_input_pullup(&DDRB,EN_DT);
    GPIO_mode_input_pullup(&DDRB,EN_CLK);

    /*-------- Initialize display --------*/
    lcd_init(LCD_DISP_ON);

    // Put string(s) on LCD screen
          // putt string "Stopky" to LCD
    lcd_gotoxy(0,0);
    lcd_puts("Stopky ");
    lcd_gotoxy(8, 0);
    lcd_puts("00:00.0");

          // putt string "Budik" to LCD 
    lcd_gotoxy(0,1);
    lcd_puts("Budik ");

  /*-------- Configure Analog-to-Digital Convertion unit --------*/
    // Select ADC voltage reference to "AVcc with external capacitor at AREF pin"
    ADMUX |= (1<<REFS0);

    // Select input channel ADC0 (voltage divider pin)
    ADMUX &= ~((1<<MUX3) | (1<<MUX2) | (1<<MUX1) | (1<<MUX0) );
    
    // Enable ADC module
    ADCSRA |= (1<<ADEN);
  
    // Enable conversion complete interrupt
    ADCSRA |=(1<<ADIE);

    // Set clock prescaler to 128
    ADCSRA |=((1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0));


  /*-------- Timers --------*/
    // Configuration of 8-bit Timer/Counter2 for Stopwatch update
    // Set the overflow prescaler to 16 ms and enable interrupt

    TIM2_overflow_16ms();
    TIM2_overflow_interrupt_enable();
    
    // Configuration of 8-bit Timer/Counter0 for Timer update
    // Set the overflow prescaler to 16 ms and enable interrupt    
    TIM0_overflow_16ms();
    TIM0_overflow_interrupt_enable();
  
    // Configure 16-bit Timer/Counter1 to start ADC conversion
    // Set prescaler to 33 ms and enable overflow interrupt
    TIM1_overflow_33ms();
    TIM1_overflow_interrupt_enable();


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
 * Function: Timer/Counter1 overflow interrupt
 * Purpose:  Single conversion mode and starting conversion every 33 ms. 
 **********************************************************************/


ISR(TIMER1_OVF_vect)
{
    // Start ADC conversion
    ADCSRA = ADCSRA | (1<<ADSC);
}


/*----------------- STOPWATCH ------------------------*/
/**********************************************************************
 * Function: Timer/Counter2 overflow interrupt
 * Purpose:  Update the stopwatch on LCD screen every sixth overflow,
 *           ie approximately every 100 ms (6 x 16 ms = 100 ms).
 **********************************************************************/

ISR(TIMER2_OVF_vect)
{ 
  static uint8_t no_of_overflows = 0;
  static uint8_t tenths = 0;  // Tenths of a second
  static uint8_t seconds = 0;   
  static uint8_t minutes = 0;
  char string[2]; 
  
  
  // reading the state of the button on joystick
  
  /***************************************************************** 
  * With the change of the state from 1 to 0, the stopwatch is started 
  * and with the change from 0 to 1 we stop the stopwatch.
  ******************************************************************/

  cs_js = GPIO_read(&PIND,JS_SW);
    if (cs_js!=ls_js)
    {
      if (GPIO_read(&PIND,JS_SW)==cs_js && cs_js==1)
      {
        if(cnt_js==0)
        {
          cnt_js++;
        }
        else
        {
          cnt_js--;
        }
      }     
    }

  ls_js=cs_js;

  no_of_overflows++;
  if (x == 511 && y == 511)
  {
    // start the stopwatch with pressed button
    if(cnt_js==0)
    { 
      if (no_of_overflows >= 6)
      {
        // Do this every 6 x 16 ms = 100 ms
        no_of_overflows = 0;
        tenths++;  

        if(tenths > 9)
        { 
          tenths = 0;
          seconds++;

          if (seconds > 59)
          {
            seconds = 0;
            minutes++;
                  
            if (minutes > 59)
            {
              minutes = 0;
            }
                  
          }    
        }
      }
    }
  }
  
  else
  {
    minutes = 0;
    seconds = 0;
    tenths = 0;
  }     

  itoa(minutes, string, 10);  // Convert decimal value to string
  lcd_gotoxy(8, 0);
  
  if (minutes < 10)
  { 
    lcd_putc('0');
  }
            
  lcd_puts(string);
  lcd_gotoxy(10, 0);
  lcd_putc(':');
  itoa(seconds, string, 10);  // Convert decimal value to string
  lcd_gotoxy(11, 0);
            
  if (seconds < 10)
  {
    lcd_putc('0');
  }
            
  lcd_puts(string);
  lcd_gotoxy(13, 0);
  lcd_putc('.');
            
  itoa(tenths, string, 10);  // Convert decimal value to string
  lcd_gotoxy(14, 0);
  lcd_puts(string);

}

/*----------------- ALARM CLOCK ------------------------*/
/**********************************************************************
 * Function: Timer/Counter0 overflow interrupt
 * Purpose:  Update the stopwatch on LCD screen every sixth overflow,
 *           ie approximately every 100 ms (6 x 16 ms = 100 ms).
 **********************************************************************/
ISR(TIMER0_OVF_vect)
{
    static uint8_t no_of_overflows = 0;
    static int8_t tenths = 0;    // Tenths of a second
    static int8_t seconds = 0;   
    static int8_t minutes = 0;
    uint8_t led_value = LOW;      // Local variable to keep LED status
    char string[2];               // String for converted numbers by itoa()
    pinMode(LED_RED, OUTPUT);     // Set pin where on-board LED is connected as output
        
  // reading the state of the button on encoder
  // with the change of the state from 1 to 0, the alarm clock is started 
  // and with the change from 0 to 1 we stop the alarm clock
 

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

    itoa(minutes, string, 10);  // Convert decimal value to string
    lcd_gotoxy(8, 1);
    if (minutes < 10)
    { 
      lcd_putc('0');
    }
    lcd_puts(string);
      
    lcd_gotoxy(10, 1);
    lcd_putc(':');

    itoa(seconds, string, 10);  // Convert decimal value to string
    lcd_gotoxy(11, 1);
      
    if (seconds < 10)
    {
      lcd_putc('0');
    }
    lcd_puts(string);

    lcd_gotoxy(13, 1);
    lcd_putc('.');
         
    itoa(tenths, string, 10);  // Convert decimal value to string
    lcd_gotoxy(14, 1);
    lcd_puts(string);

   
    // Get encoder value and change time
    cs_en_r = GPIO_read(&PINB, EN_CLK);

    if (cs_en_r != ls_en_r && cs_en_r == 1)
    {
      if(GPIO_read(&PINB, EN_DT) != cs_en_r) //rotating clockwise
      {
        seconds++;          // seconds incrementing
        if (seconds>59)     // when seconds reach value 59, set them to 0
        {
          seconds = 0;
          minutes++;          // minutes incrementing
          if (minutes>59)     // when minutes reach value 59, set them to 0
          {
            minutes = 0;    
          }
        }
        
      }

      else                   //rotating counterlockwise
      {
        seconds--;          // seconds decrementing
        if (seconds == -1)  // when seconds reach value -1, set them to 59
        {
          seconds = 59;
          minutes--;           // minutes decrementing
          if (minutes == -1)    // when minutes reach value -1, set them to 59
          {
            minutes = 59;
          }
        }
      }
    }

    ls_en_r = cs_en_r;
    
  // start the alarm clock with pressed button
    if (cnt_en==0)
    {
      // if the LED was on, turn it off
      if (led_value == HIGH)
      {
        led_value = LOW;
      } 
      digitalWrite(LED_RED, led_value);

      
      no_of_overflows++;
      
      // stop when reaching 00:00.0
      if (tenths == 0 && seconds == 0 && minutes == 0)
      {
        // Turn the LED ON if the alarm clock runs up
        if (led_value == LOW)
          led_value = HIGH;
        else
        led_value = LOW;
        digitalWrite(LED_RED, led_value);
        
      }

      // start counting down
      else 
      {
        if (no_of_overflows >=  6)
        {
          no_of_overflows = 0;
          tenths--;

          if (tenths < 0)
          { 
            tenths = 9;
            seconds--;

            if (seconds < 0)
            {
              seconds = 59;
              minutes--;
            }
          }
        }
      }       
    }
}


/*----------------- JOYSTICK POSITION ------------------------*/
/**********************************************************************
 * Function: ADC complete interrupt
 * Purpose:  Get the value of joystick position for reseting the stopwatch.
 **********************************************************************/

ISR(ADC_vect)
{
  static uint8_t channel = 0;
  if(channel == 0)
  {
    // ADMUX to read value from A0
    ADMUX &= ~((1<<MUX0) | (1<<MUX1) | (1<<MUX2) | (1<<MUX3));
    
    x = ADC;      // x axis value 
    channel++;    // set channel to 1
  }

  else if(channel == 1)
  {
    // ADMUX to read value from A1
    ADMUX &= ~((1<<MUX1) | (1<<MUX2) | (1<<MUX3)); 
    ADMUX |= (1<<MUX0);

    y = ADC;      // y axis value
    channel--;    // set channel back to 0
  }
  
}


