# Circadian Lights

This project simulates a day and night cycle using an Arduino board and a light sensor TEMP 6000. The current time acts as a reference for start of day cycle. The LED brightness changes according to the time elapsed from start time in accordance to a day and night cycle at that place.


## Description

This project uses an Arduino UNO, UNIX time data, LED plate, and a few resistors to mimic the day and night cycle based on the current time. During the day, the LED will be bright, while at night, it will be dim. It will simulate a artifical day and night cycle preferable to a particualr region. The brightness will gradually change over the course of 24 hours, simulating a natural day/night cycle.
## Requirements

to build this project, you will need the following components:

* Arduino UNO
* RTC module (DS1307 or similar) or UNIX time data
* LED plate
* 220 ohm resistor
* 10k ohm resistor
* Jumper wires
* Breadboard
* You will also need the Arduino IDE installed on your computer to upload the code to the Arduino.

## Installation
1) Connect the components on the breadboard as per the circuit diagram in the repository.
2) Connect the Arduino to your computer using a USB cable.
3) Open the Arduino IDE and load the day_night_cycle.ino sketch from the repository.
4) Verify the code and upload it to the Arduino.

## Usage
Once the code is uploaded to the Arduino, the LED will start simulating the day/night cycle based on the current time. You can adjust the brightness of the LED by changing the values of the minBrightness and maxBrightness variables in the code.

Contributing
If you'd like to contribute to this project, feel free to fork the repository and submit a pull request. Any contributions are welcome!

License
This project is licensed under the MIT License - see the LICENSE file for details.


## Contributing
If you'd like to contribute to this project, feel free to fork the repository and submit a pull request. Any contributions are welcome!
