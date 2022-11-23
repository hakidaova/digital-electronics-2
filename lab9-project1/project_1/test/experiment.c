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

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include <gpio.h>           // GPIO library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include <lcd.h>            // Peter Fleury's LCD library
#include <stdlib.h>         // C library. Needed for number conversions


/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:  Update stopwatch value on LCD screen when 8-bit 
 *           Timer/Counter2 overflows.
 * Returns:  none
 **********************************************************************/
int main(void)
{
    // Initialize display
    lcd_init(LCD_DISP_ON_CURSOR_BLINK);

    // Put string(s) on LCD screen

    lcd_gotoxy(1, 1);
    lcd_puts("b");

    lcd_gotoxy(11, 1);
    lcd_puts("c");

    // Custom character definition using https://omerk.github.io/lcdchargen/
    /*uint8_t customChar[24] = {
        0b00100,
        0b01010,
        0b10001,
        0b10000,
        0b01000,
        0b00100,
        0b00010,
        0b00001,

        0b00100,
        0b01010,
        0b10001,
        0b00001,
        0b00010,
        0b00100,
        0b01000,
        0b10000
    };

    lcd_command(1<<LCD_CGRAM);       // Set addressing to CGRAM (Character Generator RAM)
                                     // ie to individual lines of character patterns
    for (uint8_t i = 0; i < 24; i++)  // Copy new character patterns line by line to CGRAM
        lcd_data(customChar[i]);
    lcd_command(1<<LCD_DDRAM);       // Set addressing back to DDRAM (Display Data RAM)
                                     // ie to character codes

    // Display symbol with Character code 0
    lcd_gotoxy(12,1);
    lcd_putc(0x00);
    */

    // Configuration of 8-bit Timer/Counter2 for Stopwatch update
    // Set the overflow prescaler to 16 ms and enable interrupt
    TIM2_overflow_16ms();
    TIM2_overflow_interrupt_enable();
    TIM0_overflow_4ms();
    TIM0_overflow_interrupt_enable();

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
    static uint8_t tenths = 0;      // Tenths of a second
    static uint8_t seconds = 0;     // Seconds
    static uint8_t minutes = 0;     // Minutes
    char string[2];         // String for converted numbers by itoa()


    no_of_overflows++;
    if (no_of_overflows >= 6)
    {
        // Do this every 6 x 16 ms = 100 ms
        no_of_overflows = 0;
        tenths++;

        if (tenths > 9)
        {
            tenths = 0;
            seconds++;
            if (seconds > 59)
            {
                seconds = 00;
                minutes++;
            }

        }

        // Count tenth of seconds 0, 1, ..., 9, 0, 1, ...

        itoa(tenths, string, 10);  // Convert decimal value to string

        // Display "00:.tenths"
        lcd_gotoxy(7, 0);
        lcd_puts(string);

        lcd_gotoxy(6, 0);
        lcd_putc('.');

        itoa(seconds, string, 10);  // Convert decimal value to string
        lcd_gotoxy(4, 0);
        if (seconds < 10)
        {
            lcd_gotoxy(4, 0);
            lcd_puts("0");
        }
        lcd_puts(string);     

        lcd_gotoxy(3, 0);
        lcd_putc(':');
        
        itoa(minutes, string, 10);  // Convert decimal value to string
        lcd_gotoxy(1, 0);
        if (minutes < 10)
        {
            lcd_gotoxy(1, 0);
            lcd_puts("0");
        }
        lcd_puts(string); 

        itoa(pow(seconds,2), string, 10);  // Convert decimal value to string
        lcd_gotoxy(11, 0);
        lcd_puts(string);

        /* if
        lcd_gotoxy(1, 1);
        lcd_putc(0xff);
        */
    }
    // Else do nothing and exit the ISR
}


ISR(TIMER0_OVF_vect)
{
    static uint8_t symbol = 0;
    static uint8_t position = 0;
    static uint8_t no_of_overflows = 0;
    no_of_overflows++;
    if (no_of_overflows >= 5)
    {
        // Do this every 5 x 4 ms = 20 ms
        lcd_gotoxy(1+position, 1);
        lcd_putc(symbol);
        

    }
    // WRITE YOUR CODE HERE

    


    
}