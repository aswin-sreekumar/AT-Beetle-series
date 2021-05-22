# Beetle-V1-series
Features a basic 4W differential drive bot controlled using bluetooth, programmed in Arduino.

### Beetle V1 Series currently consists of 2 versions

Beetle 1.0 : Bot programmed in Arduino. Find documentation [here](https://drive.google.com/file/d/1H8mcwFhFoOXd1WlOg6coQMSA7BYLAQFO/view?usp=sharing)

Beetle 1.1 : Battery charge indicator and status LEDs added. Find documentation [here](https://drive.google.com/file/d/1WrD1UES0iQiyWsx6fhYPGwo6KrXmscAf/view?usp=sharing)

Beetle 2.0 : Bot with stand-alone Atmega328p programmed in AVR Embedded C (under development)

## Contents of repository
Beetle_1.0 - Arduino sketch for Beetle 1.0

blueBase 1.0 - Python program for PC control of Beetle 1.0 

Beetle_1.1 - Arduino sketch for Beetle 1.0

blueBase 1.1 - Python program for PC control of Beetle 1.1

## Beetle 1.0
### Design of bot
Minimalistic and compact design is the main aim of the project, still leaving a considerable space on the base considering future upgrades and expansion to project.

### Control board
Major features compared to contemporary designs:
- No jumper wires used. Entire wiring includes solder lines at bottom side and wires on top side soldered to bottom.
- Motor driver IC L293D used as the current consumption of DC motors are far less than the channel limit of the IC. The L293D facilitates continuous output current of 600mA per channel, while the motors consume only 240 mA per channel, making it an ideal choice.
- Communication module, microcontroller and motor driver embedded into a single board.
- Female headers used for replacing microcontroller and motor driver and IC base used for replacing motor driver IC (L293D).
- Connector pins used for battery power input and motor power output.
- Entire board screwed to base, making it removable.
## Beetle 1.1
### Features added:
1. Battery charge level indicator:
    - Battery level constantly monitored.
    - Transmits battery charge percentage on request.
    - Motor power cut-off at low battery voltage.
2. LEDs to display status of bot:
    - 2 x 5mm LEDs (red and blue) included in control board.
    - Red LED to indicate low battery level state.
    - Blue LED to indicate status of Bluetooth communication and bot.

### LED display status
Alternative blinking of red and blue LEDs: Initialising and setting up bot.
- Blue LED blink: Data received through HC05 module.
- Red LED: Bot’s battery is low and needs to be recharged.
### Control board
The input voltage of battery source is fed into A6 pin of Arduino Nano using a potential divider. The voltage measured is calibrated with actual data and the values are monitored constantly by the microcontroller.

## Gallery
### Circuit
![beetle 1 1_circuit](https://user-images.githubusercontent.com/63254914/119235326-91ed7180-bb4f-11eb-91d3-51cc30a711ac.jpg)

### Control board
![IMG-20200808-WA0011](https://user-images.githubusercontent.com/63254914/119235276-4f2b9980-bb4f-11eb-8984-75aa6eb50ea0.jpg)
![IMG-20200808-WA0003](https://user-images.githubusercontent.com/63254914/119235278-50f55d00-bb4f-11eb-9cfb-6d65745d95fa.jpg)

### Bot
![IMG-20200805-WA0012](https://user-images.githubusercontent.com/63254914/119235283-5a7ec500-bb4f-11eb-9b87-facc5c7fdf6c.jpeg)
![IMG-20200808-WA0029](https://user-images.githubusercontent.com/63254914/119235291-65395a00-bb4f-11eb-91e0-9f5b39a0d5e4.jpg)
![IMG-20200808-WA0020](https://user-images.githubusercontent.com/63254914/119235293-679bb400-bb4f-11eb-8ad5-d7ce69c0dbd7.jpg)
![IMG-20200808-WA0010](https://user-images.githubusercontent.com/63254914/119235300-6ec2c200-bb4f-11eb-9255-7adc4f5e693a.jpg)
![IMG-20200808-WA0013](https://user-images.githubusercontent.com/63254914/119235373-daa52a80-bb4f-11eb-9140-9453e87e79a2.jpg)

