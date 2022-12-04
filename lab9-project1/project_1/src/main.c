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
#define JS_SW PD2   // PD2 is an AVR pin where the button of the joystick is connected
#define JS_VRx PC0  // PC0 is where the VRx pin of the joystick is connected
#define JS_VRy PC1  // PC1 is where the VRy pin of the joystick is connected
#define LED_RED PB5 // PB5 is where the LED diode is connected
#define EN_SW PB2   // PB2 is an AVR pin where the button of the encoder is connected
#define EN_DT PB3   // PB3 is where the DT pin of the encoder is connected
#define EN_CLK PB4  // PB4 is where the CLK pin of the encoder is connected

#define SHORT_DELAY 250 // Delay in milliseconds
#ifndef F_CPU
# define F_CPU 16000000 // CPU frequency in Hz required for delay funcs
#endif

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <util/delay.h>     // Functions for busy-wait delay loops
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include <gpio.h>           // GPIO library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include <lcd.h>            // Peter Fleury's LCD library
#include <stdlib.h>         // C library. Needed for number conversions

// -----
// This part is needed to use Arduino functions but also physical pin
// names. We are using Arduino-style just to simplify the first lab.
#include "Arduino.h"
#define PB5 13              // In Arduino world, PB5 is called "13"



/*----- Define global variables -----*/

uint8_t ls_js, cs_js;             // last state, current state
uint8_t ls_en, cs_en;       // last state and current state of the button of the encoder 
int8_t cnt_ls = 0;
int8_t cnt_en = 0;
//uint8_t 



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

    GPIO_mode_input_nopull(&DDRB,EN_DT);
    GPIO_mode_input_nopull(&DDRB,EN_CLK);

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
  TIM0_overflow_16ms();
  TIM0_overflow_interrupt_enable();
  TIM1_overflow_4ms();
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
  char string[2];             // String for converted numbers by itoa()
    
  // reading the state of the button on joystick
  
  /*  with the change of the state from 1 to 0, the stopwatch is started 
      and with the change from 0 to 1 we stop the stopwatch
  */
  
  // lcd_gotoxy(6, 0);
  cs_js = GPIO_read(&PIND,JS_SW);
    if (cs_js!=ls_js)
    {
      if (GPIO_read(&PIND,JS_SW)==cs_js && cs_js==1)
      {
        if(cnt_ls==0)
        {
          cnt_ls++;
        }
        else
        {
          cnt_ls--;
        }
      }

      itoa(cnt_ls, string, 10);
      lcd_gotoxy(6, 0);
      lcd_puts(string);
    }

  ls_js=cs_js;

  // start the stopwatch with pressed button
  if(cnt_ls==0)
  {  
    no_of_overflows++;
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
        }    
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
  }    
  
}



/* Variables ---------------------------------------------------------*/
// Custom character definition using https://omerk.github.io/lcdchargen/
/*--------------------------------------------------------------------*/
/**
 * ISR starts when Timer/Counter0 overflows. Update the progress bar on
 * LCD display every 16 ms.
 */



ISR(TIMER0_OVF_vect)
{
    static uint8_t no_of_overflows = 0;
    static uint8_t tenths = 9;  // Tenths of a second
    static uint8_t seconds = 5;   
    static uint8_t minutes = 0;
    char string[2];             // String for converted numbers by itoa()


    // reading the state of the button on encoder
  
  /*  with the change of the state from 1 to 0, the alarm clock is started 
      and with the change from 0 to 1 we stop the alarm clock
  */

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
      
      itoa(cnt_en, string, 10);
      lcd_gotoxy(6, 1);
      lcd_puts(string);
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
  // start the alarm clock with pressed button
    if (cnt_en==0)
    {
      no_of_overflows++;
      
      if (tenths <= 1 && seconds == 0 && minutes == 0)
        {
          lcd_gotoxy(8, 1);
          lcd_putc('00:00.0');
        }
      
      
      else 
      {
      
      if (no_of_overflows >= 6)
      {
          // Do this every 6 x 16 ms = 100 ms
          no_of_overflows = 0;
          tenths--;  

          if(tenths == 0)
          { tenths = 9;
            seconds--;

            if (seconds == 0 && tenths == 0)
            {
              seconds = 59;
              minutes--;
            }
          }
      }
      
      }

      
      
        uint8_t led_value = LOW;  // Local variable to keep LED status
        
        // Set pin where on-board LED is connected as output
        pinMode(LED_RED, OUTPUT);

        // Infinite loop
        if (tenths == 1 && seconds == 0 && minutes == 0)  
        {
         // Change LED value
          if (led_value == LOW)
            led_value = HIGH;
          else
          led_value = LOW;
          // Pause several milliseconds
          //_delay_ms(SHORT_DELAY);
          // Turn ON/OFF on-board LED
          digitalWrite(LED_RED, led_value);
        }
    }

    /*
    if (seconds == 0 && minutes == 0)
      {
        cnt_en == 1;
      }
    cnt_en = cnt_en;
    */

      /* Encoder routines -------------------------------------------------*/
      /**********************************************************************
      * Function: něco
      * Purpose:  vymyslíme
      **********************************************************************/
      //EN_state = GPIO_read(&PIN,EN_SW);

      //if(EN_state >= 9)
      //{
        
      //}
    

      
    
}

ISR(TIMER1_OVF_vect)
{

 
}

/* Joystick routines -------------------------------------------------*/
/**********************************************************************
 * Function: Joystick positioning
 * Purpose:  Moving the cursor according to the joystick position.
 **********************************************************************/
// const int SW_pin = 2; // digital pin connected to SW
/*
const int VRx = 0; // analog pin connected to VRx
const int VRy = 1; // analog pin connected to VRy

void setup() 
{
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  Serial.begin(9600);
}

void loop() 
{
  Serial.print("X: ");
  Serial.print(analogRead(VRx));
  Serial.print(" Y: ");
  Serial.print(analogRead(VRy));
  Serial.print(" Z: ");
  Serial.println(digitalRead(SW_pin));
  delay(250);
}
*/


