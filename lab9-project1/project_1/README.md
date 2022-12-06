# Project 1 - Stopwatch and Timer

Application of analog joy-stick (2 ADC channels, 1 push button), rotary encoder, and Digilent PmodCLP LCD module.

The result of our project contains user-launched stopwatch and timer displayed on LCD module. The stopwatch is controlled by joystick button which starts or stops it. Pushing the button of the encoder has the same function but for timer. By rotating the encoder clockwise, the time on timer increases, decrementation is made by rotating it counterclockwise. End of the countdown process (i.e. the timer reaches 00:00.0) is signalised by a LED diode.

### Team members

* Daová Hana
* Foltyn Ondřej

## Table of contents (?)

## Hardware description

For our purposes, we use [Arduino UNO](#ArduinoUNO) that connects:
* [LCD module](#LCDmodule)
* [Analog joystick](#Analogjoystick)
* [Rotary encoder](#Rotaryencoder)
* [LED diode](#LEDdiode)

See our [wiring here](#Wiring)

<a name="ArduinoUNO"></a>
### Arduino UNO
Arduino UNO board with implemented microcontroller ATmega328 is our main component in this project. It has 14 digital GPIO input/output pins (6 PWM), 6 analog input pins, 16 MHz ceramic oscillator, a USB port which can be used as UART and a lot more.

![Arduino UNO](https://github.com/hakidaova/digital-electronics-2/blob/main/lab9-project1/images/arduino.jpeg)

> **Note:** For more information about the board see the [manual](https://docs.arduino.cc/resources/datasheets/A000066-datasheet.pdf).

<a name="LCDmodule"></a>
### LCD module
LCD module used in our project is the one with dot matrix liquid crystal display controller HD44780. The display itself has 32 individual positions for characters (predefined or custom) equally divided into 2 rows.
It is supplied by up to 5 V. 

![LCD module](https://github.com/hakidaova/digital-electronics-2/blob/main/lab9-project1/images/LCD.png)

> **Note:** For more about the Digilent PmodCLP LCD see the [manual](https://digilent.com/reference/_media/reference/pmod/pmodclp/pmodclp_rm.pdf).

<a name="Analogjoystick"></a>
### Analog joystick
![Analog joystick](https://github.com/hakidaova/digital-electronics-2/blob/main/lab9-project1/images/joy-stick.jpg)

<a name="Rotaryencoder"></a>
### Rotary encoder
![Rotary encoder](https://github.com/hakidaova/digital-electronics-2/blob/main/lab9-project1/images/rotary-encoder.jpg)

<a name="LEDdiode"></a>
### LED diode
![LED diode]()

<a name="Wiring"></a>
### Complete wiring of the system
![Wiring](https://github.com/hakidaova/digital-electronics-2/blob/main/lab9-project1/images/simulIde_schematic.png)
> **Note:** Picture was created by [SimulIDE](https://www.simulide.com/p/home.html).

Insert descriptive text and schematic(s) of your implementation.




## Software description

* [Flowcharts](#Flowcharts) for:
  * [Stopwatch](#Stopwatch)
    * [Joystick button](#Joystickbutton)
  * [Timer](#Timer)
    * [Encoder button](#Encoderbutton)
    * [Encoder rotation](#Encoderrotation)
* [Libraries](#Libraries)
  * [Description](#Description)
  * [Source files](#Sourcefiles)


<a name="Flowcharts"></a>
### Flowcharts

<a name="Stopwatch"></a>
#### Stopwatch flowchart
![Stopwatch flowchart](https://github.com/OndraFoltyn/digital-electronics-2/blob/main/project1/Stopwatch.drawio.png)

<a name="Joystickbutton"></a>
#### Joystick button flowchart
![Joystick button flowchart](https://github.com/OndraFoltyn/digital-electronics-2/blob/main/project1/Joystick_button.drawio.png)

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

<a name="Sourcefiles"></a>
#### Source files

Put flowchats of your algorithm(s). Write descriptive text of your libraries and source files. Put direct links to these files in `src` or `lib` folders.

## GitHub repository structure

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
   ├── test            // No need this
   ├── platformio.ini  // Project Configuration File
   └── README.md       // Report of this project
   ```


## Video

Insert a link to a short video with your practical implementation example (1-3 minutes, e.g. on YouTube).

## References

1. [Encoder](https://howtomechatronics.com/tutorials/arduino/rotary-encoder-works-use-arduino/?fbclid=IwAR2GDmzOCwF2mUCt-pVNGLNIA0n9qdLGAsA48_TlhPRhTdYTlosFNacai3k)
2. [LCD display](https://digilent.com/reference/_media/reference/pmod/pmodclp/pmodclp_rm.pdf)
3. [Digital Electronics 2 course run by doc. Ing. Tomáš Frýza, Ph.D.](https://github.com/tomas-fryza/digital-electronics-2)

