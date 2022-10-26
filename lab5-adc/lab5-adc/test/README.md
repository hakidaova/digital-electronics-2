# Lab 5: INSERT_YOUR_FIRSTNAME INSERT_YOUR_LASTNAME

### Analog-to-Digital Conversion

1. Complete table with voltage divider, calculated, and measured ADC values for all five push buttons.

   | **Push button** | **PC0[A0] voltage** | **ADC value (calculated)** | **ADC value (measured)** | **ADC value (measured, hex)** |
   | :-: | :-: | :-: | :-: | :-: |
   | Right  | 0&nbsp;V     | 0    | 0  | 0 |
   | Up     | 0.495&nbsp;V | 101  | 99 | 63f |
   | Down   | 1.203&nbsp;V | 246  | 257 | 101 |
   | Left   | 1.969&nbsp;V | 403  | 409 | 199 |
   | Select | 3.181&nbsp;V | 651  | 639 | 27f |
   | none   | 5.000&nbsp;V | 1023 | 1023 | 0ff |

| **Operation** | **Register(s)** | **Bit(s)** | **Description** |
   | :-- | :-: | :-: | :-- |
   | Voltage reference    | ADMUX  | REFS1:0 | 00: ..., 01: AVcc voltage reference (5V), ... |
   | Input channel        | ADMUX  | MUX3:0 | 0000: ADC0, 0001: ADC1, ...|
   | ADC enable           | ADCSRA | ADEN | 1 |
   | Start conversion     | ADCSRA | ADSC | 1 |
   | ADC interrupt enable | ADCSRA | ADIE | 1 |
   | ADC clock prescaler  | ADCSRA | ADPS2:0 | 000: Division factor 2, 001: 2, 010: 4, ...|
   | ADC 10-bit result    | ADCL and ADCH |  |  |

### Temperature meter

Consider an application for temperature measurement. Use analog temperature sensor [TC1046](http://ww1.microchip.com/downloads/en/DeviceDoc/21496C.pdf), LCD, and a LED. Every 30 seconds, the temperature is measured and the value is displayed on LCD screen. When the temperature is too high, the LED will turn on.

2. Draw a schematic of temperature meter. The image can be drawn on a computer or by hand. Always name all components and their values.

   ![your figure]()

3. Draw two flowcharts for interrupt handler `TIMER1_OVF_vect` (which overflows every 1&nbsp;sec) and `ADC_vect`. The image can be drawn on a computer or by hand. Use clear descriptions of the individual steps of the algorithms.

   ![your figure]()