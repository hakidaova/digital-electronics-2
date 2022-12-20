# Project 2

Precise generation of several PWM channels. Application of two (or more) Servo motors SG90.

## Instructions

The goal of the project is cooperation in pairs, further study of the topic, design of own solutions, implementation, creation of project documentation and presentation of results. The division of roles and tasks within the team is up to their members.

* Students work on a project in the labs during the 12th and 13th weeks of the semester.

* Through the BUT e-learning, students submit a link to the GitHub repository, which contains the complete project in PlatfomIO and a descriptive README file. The submission deadline is the day before the next laboratory, i.e. in 2 weeks.

* The source code for the AVR must be written in C and/or Assembly and must be implementable on Arduino Uno board using toolchains from the semester, ie PlatformIO and not in the Arduino-style. No other development tools are allowed.

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
* [2 Servo motors](#Servomotor)
* [Rotary encoder](#Rotaryencoder)

See our [wiring here](#Wiring)

<a name="ArduinoUNO"></a>
### Arduino UNO
Arduino UNO board with implemented microcontroller ATmega328 is our main component in this project. It has 14 digital GPIO input/output pins (6 PWM), 6 analog input pins, 16 MHz ceramic oscillator, a USB port which can be used as UART and by which we connected it to the computer to load our programming code.

![Arduino UNO](https://github.com/hakidaova/digital-electronics-2/blob/main/lab9-project1/images/arduino.jpeg)

> **Note:** For more information about the board see the [manual](https://docs.arduino.cc/resources/datasheets/A000066-datasheet.pdf).

<a name="Servomotor"></a>
### Servo motor
description

![Servo motor](https://github.com/hakidaova/digital-electronics-2/blob/main/lab10-project2/images/servo.jpg)

> **Note:** For more information about the board see the [manual](https://docs.arduino.cc/resources/datasheets/A000066-datasheet.pdf).

<a name="Rotaryencoder"></a>
### Rotary encoder
Encoder which we rotate with is used as a time changer for our timer. The rotation is based on combining 2 output signals inside the encoder. If the outputs are both the same, encoder was rotated clockwise and the time is set up. If we rotate it counterclockwise, the outputs will be the exact opposite of each other and our time is set down.

![Rotary encoder](https://github.com/hakidaova/digital-electronics-2/blob/main/lab9-project1/images/rotary-encoder.jpg)

<a name="Wiring"></a>
### Complete wiring of the system
You can see below how the components are connected altogether...

![Wiring IRL](https://github.com/hakidaova/digital-electronics-2/blob/main/lab10-project2/images/wiring.jpeg)

...and once again here for clearer view on exact pins. (Pins for Vcc and GND are not pictured but they are in every component and are used!)

![Wiring](https://github.com/hakidaova/digital-electronics-2/blob/main/lab10-project2/images/simullIde-schematic.jpeg)
> **Note:** Picture was created by [SimulIDE](https://www.simulide.com/p/home.html).
> 
<a name="Software"></a>
## Software description

* [Flowcharts](#Flowcharts) for:
   * [Encoder button](#Encoderbutton)
   * [Encoder rotation](#Servosrotating)
* [Libraries](#Libraries)
  * [Description](#Description)
  * [Source files](#Sourcefiles)

<a name="Flowcharts"></a>
### Flowcharts

<a name="Encoderbutton"></a>
#### Encoder button flowchart
![Encoder button flowchart](https://github.com/OndraFoltyn/digital-electronics-2/blob/main/projects/project1/Encoder_button.drawio.png)

<a name="Servosrotating"></a>
#### Flowchart of rotating with the encoder and the motors 
![Encoder rotation](https://github.com/OndraFoltyn/digital-electronics-2/blob/main/projects/project2/rotating_servos.drawio.svg)

<a name="Libraries"></a>
### Libraries

<a name="Description"></a>
#### Description
1. ***GPIO*** allows us to controll AVRs' gpio pins, i.e. reading/setting values, enabling pull-ups.
2. ***TIMER*** makes it possible to control the built in registers for timer modules.
3. ***SOURCE*** is where our main code is. This part builds up the system the way we want it to work and virtually connects the pins to Arduino board.
4. ***AVR*** contains codes and definitions for the built in AVR microcontrollers.

<a name="Sourcefiles"></a>
#### Source files
1. GPIO
   1. [gpio.h](https://github.com/hakidaova/digital-electronics-2/blob/main/lab10-project2/project2/lib/gpio/gpio.h)
   2. [gpio.c](https://github.com/hakidaova/digital-electronics-2/blob/main/lab10-project2/project2/lib/gpio/gpio.c)
2. TIMER
   1. [timer.h](https://github.com/hakidaova/digital-electronics-2/blob/main/lab10-project2/project2/include/timer.h)
3. SOURCE
   1. [main.c](https://github.com/hakidaova/digital-electronics-2/blob/main/lab10-project2/project2/src/main.c)

## Structure of our project code
   ```c
   YOUR_PROJECT        // PlatfomIO project
   ├── include         // Included files
       └── timer.h  
   ├── lib             // Libraries
       └── gpio
           └── gpio.c
           └── gpio.h
   ├── src             // Source file(s)
   │   └── main.c
   ├── test            // Temporary/support files
   ├── platformio.ini  // Project Configuration File
   └── README.md       // Report of this project
   ```

<a name="Video"></a>
## Video

Here is how our servo motors work:

![](https://github.com/hakidaova/digital-electronics-2/blob/main/lab10-project2/images/vid.mp4)

<a name="References"></a>
## References

1. [Digital Electronics 2](https://github.com/tomas-fryza/digital-electronics-2) course run by doc. Ing. Tomáš Frýza, Ph.D.
2. [ATmega328P Datasheet](https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf)
3. [Servo motors article](https://navody.dratek.cz/arduino-projekty/servo-motor.html) in Czech language
