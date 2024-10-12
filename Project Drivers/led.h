 /******************************************************************************
 *
 * Module: LED
 *
 * File Name: led.h
 *
 * Description: Header file for the ATmega16 LED driver
 *
 * Author: Medhat Adel Tawfik
 *
 *******************************************************************************/

#ifndef LED_H_
#define LED_H_

#include "std_types.h"

// Define LED identifiers
typedef enum {
    LED_RED = 0,
    LED_GREEN = 1,
    LED_BLUE = 2
} LED_ID;

// Function to initialize the LEDs
void LEDS_init(void);

// Function to turn on a specific LED
void LED_on(LED_ID id);

// Function to turn off a specific LED
void LED_off(LED_ID id);

#endif /* LED_H_ */
