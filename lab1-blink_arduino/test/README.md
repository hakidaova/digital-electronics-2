# Lab 1: HANA DAOVÁ

### Morse code

1. Listing of C code which repeats one "dot" and one "comma" (BTW, in Morse code it is letter `A`) on a LED. Always use syntax highlighting, meaningful comments, and follow C guidelines:

```c
int main(void)
{
    uint8_t led_value_l = LOW;  // Local variable to keep LED status
    uint8_t led_value_h = HIGH;  // Local variable to keep LED status

    // Set pin where on-board LED is connected as output
    pinMode(LED_GREEN, OUTPUT);

    // Infinite loop
    while (1)
    {
        // Letter `A` Morse code

        //Turn the LED on
        digitalWrite(LED_GREEN, led_value_h);
        // Dot duration
        _delay_ms(SHORT_DELAY); // SHORT_DELAY 250 - Delay in milliseconds

        //Turn the LED off
        digitalWrite(LED_GREEN, led_value_l);
        // Pause duration
        _delay_ms(MID_DELAY); // MID_DELAY 500 - Delay in milliseconds

        //Turn the LED on
        digitalWrite(LED_GREEN, led_value_h);
        // Comma duration
        _delay_ms(LONG_DELAY); // LONG_DELAY 1000 - Delay in milliseconds

        //Turn the LED off
        digitalWrite(LED_GREEN, led_value_l);
        // Pause duration
        _delay_ms(MID_DELAY); // MID_DELAY 500 - Delay in milliseconds
    }

    // Will never reach this
    return 0;
}
```

2. Scheme of Morse code application, i.e. connection of AVR device, LED, resistor, and supply voltage. The image can be drawn on a computer or by hand. Always name all components and their values!

   ![Schematic](https://github.com/hakidaova/digital-electronics-2/blob/main/lab1-blink_arduino/images/schematic.png)
