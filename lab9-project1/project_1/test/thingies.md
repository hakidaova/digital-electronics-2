uint8_t led_value = LOW;  // Local variable to keep LED status

    // Set pin where on-board LED is connected as output
    pinMode(LED_RED, OUTPUT);

    // Infinite loop
    while (1)
    {
        // Change LED value
        if (led_value == LOW)
            led_value = HIGH;
        else
            led_value = LOW;
        // Pause several milliseconds
        _delay_ms(SHORT_DELAY);
        // Turn ON/OFF on-board LED
        digitalWrite(LED_RED, led_value);
    }



if (seconds <= 50)
    {
      uint8_t led_value = LOW;  // Local variable to keep LED status
      
        // Set pin where on-board LED is connected as output
        pinMode(LED_RED, OUTPUT);

        // Infinite loop
        if (seconds <= 50)
        {
          // Change LED value
          if (led_value == LOW)
            led_value = HIGH;
          else
           led_value = LOW;
          // Pause several milliseconds
          _delay_ms(SHORT_DELAY);
          // Turn ON/OFF on-board LED
          digitalWrite(LED_RED, led_value);
        }
        else 
        {
                
        }