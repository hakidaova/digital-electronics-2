# Project 1 - Stopwatch and Timer

Application of analog joy-stick (2 ADC channels, 1 push button), rotary encoder, and Digilent PmodCLP LCD module.

The result of our project contains user-launched stopwatch and timer displayed on LCD module. The stopwatch is controlled by joystick button which starts it, stops it or resets it. Pushing the button of the encoder starts or stops the for timer. By rotating the encoder clockwise, the time on timer increases, decrementation is made by rotating it counterclockwise. End of the countdown process (i.e. the timer reaches 00:00.0) is signalised by a LED diode.

### Team members

* Daová Hana
* Foltyn Ondřej

## Table of contents
* [Hardware](#Hardware)
* [Software](#Software)
* [Video](#Video)
* [References](#References)

<a name="Hardware"></a>
## Hardware description

For our purposes, we use [Arduino UNO](#ArduinoUNO) that connects:
* [LCD module](#LCDmodule)
* [Analog joystick](#Analogjoystick)
* [Rotary encoder](#Rotaryencoder)
* [LED diode](#LEDdiode)

See our [wiring here](#Wiring)

<a name="ArduinoUNO"></a>
### Arduino UNO
Arduino UNO board with implemented microcontroller ATmega328 is our main component in this project. It has 14 digital GPIO input/output pins (6 PWM), 6 analog input pins, 16 MHz ceramic oscillator, a USB port which can be used as UART and by which we connected it to the computer to load our programming code.

![Arduino UNO](https://github.com/hakidaova/digital-electronics-2/blob/main/lab9-project1/images/arduino.jpeg)

> **Note:** For more information about the board see the [manual](https://docs.arduino.cc/resources/datasheets/A000066-datasheet.pdf).

<a name="LCDmodule"></a>
### LCD module
LCD module used in our project is the one with dot matrix liquid crystal display controller HD44780. The display itself has 32 individual positions for characters (predefined or custom) equally divided into 2 rows.
It is supplied by up to 5 V. The LCD shows us the times for both stopwatch and timer. 

![LCD module](https://github.com/hakidaova/digital-electronics-2/blob/main/lab9-project1/images/LCD.png)

> **Note:** For more about the Digilent PmodCLP LCD see the [manual](https://digilent.com/reference/_media/reference/pmod/pmodclp/pmodclp_rm.pdf).

<a name="Analogjoystick"></a>
### Analog joystick
The analog joystick has 2 ADC channels which allow us to control processes in 2 directions and to read them as X, Y coordinates thanks to VRx and VRy pins. We programmed it to reset our stopwatch when it is not in its default position and it is not pressed. We also used its SW pin as a button for starting/stopping our stopwatch.
![Analog joystick](https://github.com/hakidaova/digital-electronics-2/blob/main/lab9-project1/images/joy-stick.jpg)

<a name="Rotaryencoder"></a>
### Rotary encoder
Encoder which we rotate with is used as a time changer for our timer. The rotation is based on combining 2 output signals inside the encoder. If the outputs are both the same, encoder was rotated clockwise and the time is set up. If we rotate it counterclockwise, the outputs will be the exact opposite of each other and our time is set down.

![Rotary encoder](https://github.com/hakidaova/digital-electronics-2/blob/main/lab9-project1/images/rotary-encoder.jpg)

<a name="LEDdiode"></a>
### LED diode
Our external LED diode is connected to the board with a resistor so it wouldn't get destroyed. The connection was made as active high, which means that the diode lights up when the input is set to 1. Its function is to signalize that the timer already ran out.
![LED diode](vyfotit)

<a name="Wiring"></a>
### Complete wiring of the system
You can see below how the components are connected altogether. (Pins for Vcc and GND are not pictured but they are in every component and are used!)

![Wiring](https://github.com/hakidaova/digital-electronics-2/blob/main/lab9-project1/images/simulIde_schematic.png)
> **Note:** Picture was created by [SimulIDE](https://www.simulide.com/p/home.html).

<a name="Software"></a>
## Software description

* [Flowcharts](#Flowcharts) for:
  * [ADC conversion](#ADC_conversion)
  * [Stopwatch](#Stopwatch)
    * [Joystick button](#Joystickbutton)
    * [Joystick movement](#Joystick_value)
  * [Timer](#Timer)
    * [Encoder button](#Encoderbutton)
    * [Encoder rotation](#Encoderrotation)
* [Libraries](#Libraries)
  * [Description](#Description)
  * [Source files](#Sourcefiles)


<a name="Flowcharts"></a>
### Flowcharts

<a name="ADC_conversion"></a>
#### ADC conversion flowchart
![ADC conversion](https://github.com/OndraFoltyn/digital-electronics-2/blob/main/project1/ADC_conv.drawio.png)

<a name="Stopwatch"></a>
#### Stopwatch flowchart
![Stopwatch flowchart](https://github.com/OndraFoltyn/digital-electronics-2/blob/main/project1/Stopwatch.drawio.png)

<a name="Joystickbutton"></a>
#### Joystick button flowchart
![Joystick button flowchart](https://github.com/OndraFoltyn/digital-electronics-2/blob/main/project1/Joystick_button.drawio.png)

<a name="Joystick_value"></a>
#### Joystick movement
![ADC conversion](https://github.com/OndraFoltyn/digital-electronics-2/blob/main/project1/joystick.drawio.svg)

<a name="Timer"></a>
#### Timer flowchart
![Stopwatch flowchart](https://github.com/OndraFoltyn/digital-electronics-2/blob/main/project1/timer.drawio.png)

<a name="Encoderbutton"></a>
#### Encoder button flowchart
![Encoder button flowchart](https://github.com/OndraFoltyn/digital-electronics-2/blob/main/project1/Encoder_button.drawio.png)

<a name="Encoderrotation"></a>
#### Encoder rotation flowchart
![Encoder rotation](https://github.com/OndraFoltyn/digital-electronics-2/blob/main/project1/Time_changing.drawio.png)


<a name="Libraries"></a>
### Libraries

<a name="Description"></a>
#### Description
1. GPIO 
   * allows us to controll AVRs' gpio pins, i.e. reading/setting values, enabling pull-ups.
2. LCD
   * is a library using [Peter Fleury's](https://github.com/hakidaova/digital-electronics-2/blob/main/lab9-project1/project_1/lib/lcd/lcd.h) functions for basic operations with LCD display.
3. TIMER
   * makes it possible to controll the built in registers for timer modules.
4. SOURCE
   * is where our main code is. This part builds up the system the way we want it to work and virtually connects the pins to Arduino board.
5. AVR
   * contains codes and definitions for the built in AVR microcontrollers.
6. ARDUINO
   * is

<a name="Sourcefiles"></a>
#### Source files
1. GPIO
   1. [gpio.h](https://github.com/hakidaova/digital-electronics-2/blob/main/lab9-project1/project_1/lib/gpio/gpio.h)
   2. [gpio.c](https://github.com/hakidaova/digital-electronics-2/blob/main/lab9-project1/project_1/lib/gpio/gpio.c)
2. LCD
   1. [lcd.c](https://github.com/hakidaova/digital-electronics-2/blob/main/lab9-project1/project_1/lib/gpio/lcd.c)
   2. [lcd.h](https://github.com/hakidaova/digital-electronics-2/blob/main/lab9-project1/project_1/lib/lcd/lcd.h)
   3. [lcd_definitions.h](https://github.com/hakidaova/digital-electronics-2/blob/main/lab9-project1/project_1/lib/lcd/lcd_definitions.h)
3. TIMER
   1. [timer.h](https://github.com/hakidaova/digital-electronics-2/blob/main/lab9-project1/project_1/include/timer.h)
4. SOURCE
   1. [main.c](https://github.com/hakidaova/digital-electronics-2/blob/main/lab9-project1/project_1/src/main.c)

Put flowchats of your algorithm(s). Write descriptive text of your libraries and source files. Put direct links to these files in `src` or `lib` folders.

## Structure of our projeect code

   ```c
   ├── include         // Included files
       └── timer.h  
   ├── lib             // Libraries
       └── gpio
           └── gpio.c
           └── gpio.h
       └── lcd
           └── ldc_definitions.h
           └── lcd.h
           └── lcd.c
   ├── src             // Source file(s)
   │   └── main.c
   ├── test            // Temporary/support files
   ├── platformio.ini  // Project Configuration File
   └── README.md       // Report of this project
   ```

<a name="Video"></a>
## Video

Insert a link to a short video with your practical implementation example (1-3 minutes, e.g. on YouTube).

<a name="References"></a>
## References

1. [Encoder](https://howtomechatronics.com/tutorials/arduino/rotary-encoder-works-use-arduino/?fbclid=IwAR2GDmzOCwF2mUCt-pVNGLNIA0n9qdLGAsA48_TlhPRhTdYTlosFNacai3k)
2. [LCD display](https://digilent.com/reference/_media/reference/pmod/pmodclp/pmodclp_rm.pdf)
3. [Digital Electronics 2](https://github.com/tomas-fryza/digital-electronics-2) course run by doc. Ing. Tomáš Frýza, Ph.D.
4. [Arduino UNO board](https://docs.arduino.cc/resources/datasheets/A000066-datasheet.pdf)

