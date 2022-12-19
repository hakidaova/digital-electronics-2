# Project 2

Precise generation of several PWM channels. Application of two (or more) Servo motors SG90.

## Instructions

The goal of the project is cooperation in pairs, further study of the topic, design of own solutions, implementation, creation of project documentation and presentation of results. The division of roles and tasks within the team is up to their members.

* Students work on a project in the labs during the 12th and 13th weeks of the semester.

* Through the BUT e-learning, students submit a link to the GitHub repository, which contains the complete project in PlatfomIO and a descriptive README file. The submission deadline is the day before the next laboratory, i.e. in 2 weeks.

* The source code for the AVR must be written in C and/or Assembly and must be implementable on Arduino Uno board using toolchains from the semester, ie PlatformIO and not in the Arduino-style. No other development tools are allowed.

## Recommended README.md file structure

### Team members

* Daová Hana
* Foltyn Ondřej

## Hardware description

Insert descriptive text and schematic(s) of your implementation.

## Software description

* [Flowcharts](#Flowcharts) for:

<a name="Encoderbutton"></a>
#### Encoder button flowchart
![Encoder button flowchart](https://github.com/OndraFoltyn/digital-electronics-2/blob/main/projects/project1/Encoder_button.drawio.png)

<a name="Servosrotating"></a>
#### Flowchart of rotating with the encoder and the motors 
![Encoder rotation](https://github.com/OndraFoltyn/digital-electronics-2/blob/main/projects/project2/rotating_servos.drawio.svg)

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

<a name="Libraries"></a>
### Libraries

<a name="Description"></a>
#### Description
1. ***GPIO*** allows us to controll AVRs' gpio pins, i.e. reading/setting values, enabling pull-ups.
2. ***TIMER*** makes it possible to control the built in registers for timer modules.
3. ***SOURCE*** is where our main code is. This part builds up the system the way we want it to work and virtually connects the pins to Arduino board.
4. ***AVR*** contains codes and definitions for the built in AVR microcontrollers.
5. ***ARDUINO*** library simplifies the usage of Arduino functions.

<a name="Sourcefiles"></a>
#### Source files
1. GPIO
   1. [gpio.h](https://github.com/hakidaova/digital-electronics-2/blob/main/lab10-project2/project2/lib/gpio/gpio.h)
   2. [gpio.c](https://github.com/hakidaova/digital-electronics-2/blob/main/lab10-project2/project2/lib/gpio/gpio.c)
2. TIMER
   1. [timer.h](https://github.com/hakidaova/digital-electronics-2/blob/main/lab10-project2/project2/include/timer.h)
3. SOURCE
   1. [main.c](https://github.com/hakidaova/digital-electronics-2/blob/main/lab10-project2/project2/src/main.c)

## Video

Insert a link to a short video with your practical implementation example (1-3 minutes, e.g. on YouTube).

## References

1. Write your text here.
2. ...
