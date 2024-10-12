![Car Parking System - Proteus 8 Professional - Schematic Capture 10_12_2024 10_34_10 PM](https://github.com/user-attachments/assets/53fc7812-7f09-4467-9e4d-be25a6593b02)


# Car Parking Sensor Using ATmega32, Ultrasonic Sensor, LCD Display, LEDs, and Buzzer

## Project Overview

This project implements a car parking sensor system using an ATmega32 microcontroller, an ultrasonic sensor, an LCD display, LEDs, and a buzzer. The system helps drivers detect obstacles while parking by measuring the distance to nearby objects and providing both visual and auditory feedback. The measured distance is displayed on an LCD screen, while LEDs and a buzzer alert the driver based on the proximity of the object.

## Features

- **Ultrasonic Distance Measurement:** Uses an HC-SR04 ultrasonic sensor to measure the distance between the car and nearby objects.
- **LCD Display:** Shows the measured distance in centimeters. Displays "Stop" when the distance is less than 5 cm.
- **LED Indicators:** Three LEDs (Red, Green, and Blue) indicate proximity:
  - Red LED: > 20 cm
  - Green + Red LEDs: 11-15 cm
  - Blue + Green + Red LEDs: 6-10 cm
- **Buzzer Alert:** Activates when the object is too close (≤ 5 cm).
- **Dynamic LED Behavior:** LEDs turn ON/OFF based on distance:
  - ≤ 5 cm: All LEDs flash, buzzer sounds, LCD displays "Stop."
  - 6-10 cm: All LEDs ON, no buzzer.
  - 11-15 cm: Red and Green LEDs ON, Blue LED OFF.
  - 16-20 cm: Only Red LED ON.
  - > 20 cm: All LEDs OFF, buzzer OFF.

## Hardware Components

- **ATmega32 Microcontroller**
- **HC-SR04 Ultrasonic Sensor**
- **16x2 LCD Display**
- **Red, Green, and Blue LEDs**
- **Buzzer**

## Pin Connections

- **ATmega32:**
  - **PA1 (RS), PA2 (E), PA3-PA6 (D4-D7):** Connected to LCD.
  - **PC0-PC2:** Connected to Red, Green, and Blue LEDs respectively.
  - **PC5:** Connected to the transistor controlling the buzzer.
  - **PD6 (Echo), PD7 (Trigger):** Connected to the Ultrasonic sensor.
  
- **Ultrasonic Sensor:**
  - **Echo:** PD6
  - **Trigger:** PD7

- **LEDs:**
  - **Red LED:** PC0
  - **Green LED:** PC1
  - **Blue LED:** PC2

- **Buzzer:**
  - Connected to PC5.

## Operation Description

1. The ultrasonic sensor emits ultrasonic waves and listens for their reflection from nearby objects.
2. The ATmega32 microcontroller calculates the distance based on the time taken for the wave to return.
3. The measured distance is displayed in real time on the LCD screen.
4. LEDs and the buzzer provide visual and auditory warnings based on proximity:
   - If the distance is less than or equal to 5 cm, all LEDs flash, the buzzer sounds, and "Stop" is displayed.
   - For distances between 6-20 cm, the LEDs light up progressively as the object gets closer.

## Distance Mapping

- **≤ 5 cm:** All LEDs flash, buzzer sounds, LCD shows "Stop."
- **6-10 cm:** All LEDs ON, no buzzer.
- **11-15 cm:** Red and Green LEDs ON, Blue LED OFF.
- **16-20 cm:** Only Red LED ON.
- **> 20 cm:** All LEDs OFF, buzzer OFF.

## Layered Architecture

The project uses a modular approach, separating the code into drivers and application layers.

### Drivers Implemented:
1. **GPIO Driver:**
   - Uses the GPIO driver from the course to manage LED, buzzer, and LCD control.

2. **ICU Driver:**
   - Configured to detect rising and falling edges with a prescaler of `F_CPU/8` for precise timing.
   - Functions:
     - `ICU_init()`: Initializes the ICU module.
     - `ICU_setCallBack()`: Sets the ICU callback function.
  
3. **Buzzer Driver:**
   - Functions:
     - `Buzzer_init()`: Initializes the buzzer pin and turns it off initially.
     - `Buzzer_on()`: Activates the buzzer.
     - `Buzzer_off()`: Deactivates the buzzer.

4. **LCD Driver:**
   - Utilizes the LCD driver from the course in 4-bit mode to display the distance and "Stop" warning.

5. **Ultrasonic Driver:**
   - Functions:
     - `Ultrasonic_init()`: Initializes the ICU and ultrasonic sensor.
     - `Ultrasonic_Trigger()`: Sends a trigger pulse.
     - `Ultrasonic_readDistance()`: Measures the distance.
     - `Ultrasonic_edgeProcessing()`: Callback function to calculate pulse time from the ultrasonic sensor.

## Requirements

- **Microcontroller:** ATmega32
- **System Frequency:** 16 MHz

## How to Use

1. Connect the hardware components as per the pin configuration.
2. Load the firmware onto the ATmega32 microcontroller.
3. Power up the system and place objects at varying distances in front of the ultrasonic sensor to observe the LED and buzzer behavior.

Feel free to contribute to the project by creating pull requests or submitting issues on GitHub!

## Author

Medhat Adel Tawfik
