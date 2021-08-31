# External Storage for STM32
## Abstract
On the Illini EV Concept car team, there has been a growth in the development of GPS, telemetry, and computer vision software. All these projects require various sensors that will be mounted on the car. My plan is to create a board that will be able to take the data from those sensors and store it for future use. I'll use an optical encoder to determine how fast the car is travelling, a voltage sensor to monitor the battery, and potentially a GPS module to locate the car. I will also create a custom PCB to mount components such as the SD card socket and connectors for the sensors. This project will utilize C and the SPI protocol for data transfer.

## Project Goals
### First Demonstration:
My goal for the first demo is to have the file system set up on the SD card and be able to read/write to it.

## Second Demonstration:
My goal for the second demo is to be able to use the sensors to automatically write to the SD card at an interval set by the user.

## Final Demonstration:
My goal for the final demo is to have a fully functioning board that takes sensor data and writes it to the SD card in a simple and easy-to-read format.
