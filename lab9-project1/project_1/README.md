# Project 1 - Stopwatch and Timer

Application of analog joy-stick (2 ADC channels, 1 push button), rotary encoder, and Digilent PmodCLP LCD module.

The result of our project contains user-launched stopwatch and timer displayed on LCD module. The stopwatch is controlled by joystick button which starts or stops it. Pushing the button of the encoder has the same function but for timer. By rotating the encoder clockwise, the time on timer increases, decrementation is made by rotating it counterclockwise. End of the countdown process (i.e. the timer reaches 00:00.0) is signalised by a LED diode.

### Team members

* Daová Hana
* Foltyn Ondřej

## Table of contents (?)

## Hardware description

For our purposes, we use:
* [Arduino UNO](#ArduinoUNO)
* [LCD module](#LCDmodule)
* [Analog joystick](#Analogjoystick)
* [Rotary encoder](#Rotaryencoder)
* [LED diode](#LEDdiode)

<a name="ArduinoUNO"></a>
### Arduino UNO
bflmpsvz

<a name="LCDmodule"></a>
### LCD module
zscrcjdtn

<a name="Analogjoystick"></a>
### Analog joystick
hchkrdtn

<a name="Rotaryencoder"></a>
### Rotary encoder
zscrcjdtn

<a name="LEDdiode"></a>
### LED diode
zscrcjdtn

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
bflmpsvz

<a name="Stopwatch"></a>
#### Stopwatch flowchart

<a name="Joystickbutton"></a>
#### Joystick button flowchart
![Joystick button flowchart](https://github.com/OndraFoltyn/digital-electronics-2/blob/main/project1/Joystick_button.drawio.png)

<a name="Timer"></a>
#### Stopwatch flowchart

<a name="Encoderbutton"></a>
#### Encoder button flowchart

<a name="Encoderrotation"></a>
#### Encoder rotation flowchart


<a name="Libraries"></a>
### Libraries
bflmpsvz

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

