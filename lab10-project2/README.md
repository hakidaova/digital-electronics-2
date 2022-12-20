# Project 2

Precise generation of several PWM channels. Application of two (or more) Servo motors SG90.

The goal of our project was to create a system that would use Arduino Uno's built in PWM to moderate 2 servo motors. For managing them, we used a rotary encoder.

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
Servo motors are mainly used for setting certain positions and maintaining them. Most of them can be found in robotics or automated manufacturing. The motors usually have 3 wires - the red one is for Vcc, the brown (or black) for GND and the orange (or yellow) one is for PWM. They can only be rotated by maximally 180 degrees, so in our project we set the default position of **Servo 1** to 0° (minimum) and the **Servo 2**'s to 180° (maximum).

![Servo motor](https://github.com/hakidaova/digital-electronics-2/blob/main/lab10-project2/images/servo.jpg)


<a name="Rotaryencoder"></a>
### Rotary encoder
The encoder's button is used as a selector of the servo motor we want to operate with. Rotation of the encoder is based on combining 2 output signals inside the encoder. If the outputs are both the same, encoder was rotated clockwise and the **Servo 1** is rotated (if it has been chosen) by up to 180° clockwise. After reaching the maximum position (180°), the motor goes back to its default position (0°). **Servo 2** doesn't react to this operation even when it's chosen. If we rotate the encoder counterclockwise, **Servo 2** is rotated (if it has been chosen) by up to 180° counterclockwise. After reaching the minimum position (0°), the motor goes back to its default position (180°). **Servo 1** doesn't react to this operation even when it is chosen.

![Rotary encoder](https://github.com/hakidaova/digital-electronics-2/blob/main/lab9-project1/images/rotary-encoder.jpg)

<a name="Wiring"></a>
### Complete wiring of the system
You can see below how the components are connected altogether...

![Wiring IRL](https://github.com/hakidaova/digital-electronics-2/blob/main/lab10-project2/images/wiring.jpeg)

...and once again here for clearer view on exact pins. (We had to change the PWM pins from 5 and 6 to 9 and 10 because we wanted to work with registers OC1A/B)

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

![](https://github.com/hakidaova/digital-electronics-2/blob/main/lab10-project2/images/video.gif)

<a name="References"></a>
## References

1. [Digital Electronics 2](https://github.com/tomas-fryza/digital-electronics-2) course run by doc. Ing. Tomáš Frýza, Ph.D.
2. [ATmega328P Datasheet](https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf)
3. [Servo motors article](https://navody.dratek.cz/arduino-projekty/servo-motor.html) in Czech language
