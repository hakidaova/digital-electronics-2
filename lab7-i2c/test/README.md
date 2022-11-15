# Lab 7: Hana Daová

### Arduino Uno pinout

1. In the picture of the Arduino Uno board, mark the pins that can be used for the following functions/operations:
   * PWM generators from Timer0, Timer1, Timer2: **PB3, PB2, PB1, PD6, PD5, PD3**
   * analog channels for ADC: **PC0:PC5**
   * UART pins: **PD1, PD0**
   * I2C pins: **PC1, PC0**
   * SPI pins: **PB2:PB5**
   * external interrupt pins INT0, INT1: **PD3, PD2**

   ![your figure](https://github.com/hakidaova/digital-electronics-2/blob/main/lab7-i2c/test/images/PinOut.png)

### I2C communication

2. Draw a timing diagram of I2C signals when calling function `rtc_read_years()`. Let this function reads one byte-value from RTC DS3231 address `06h` (see RTC datasheet) in the range `00` to `99`. Specify when the SDA line is controlled by the Master device and when by the Slave device. Draw the whole request/receive process, from Start to Stop condition. The image can be drawn on a computer (by [WaveDrom](https://wavedrom.com/) for example) or by hand. Name all parts of timing diagram.

   ![your figure]()

### Meteo station

Consider an application for temperature and humidity measurements. Use sensor DHT12, real time clock DS3231, LCD, and one LED. Every minute, the temperature, humidity, and time is requested from Slave devices and values are displayed on LCD screen. When the temperature is above the threshold, turn on the LED.

3. Draw a flowchart of `TIMER1_OVF_vect` (which overflows every 1&nbsp;sec) for such Meteo station. The image can be drawn on a computer or by hand. Use clear description of individual algorithm steps.

   ![your figure]()
