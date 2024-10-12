/******************************************************************************
 *
 * Module: LED
 *
 * File Name: led.c
 *
 * Description: Source file for the ATmega16 LED driver
 *
 * Author: Medhat Adel Tawfik
 *
 *******************************************************************************/

#include "gpio.h"
#include "led.h"
#include "avr/io.h"
#include "Common_Macros.h"  // Include the macros for bit manipulation

void LEDS_init(void) {
    // Configure the pins for Red, Green, Blue LEDs
    GPIO_setupPinDirection(PORTC_ID, PIN0_ID, PIN_OUTPUT);
    GPIO_setupPinDirection(PORTC_ID, PIN1_ID, PIN_OUTPUT);
    GPIO_setupPinDirection(PORTC_ID, PIN2_ID, PIN_OUTPUT);
    LED_off(LED_RED);
    LED_off(LED_GREEN);
    LED_off(LED_BLUE);
}

void LED_on(LED_ID id) {
    SET_BIT(PORTC, id);  // Use the SET_BIT macro to turn on the LED
}

void LED_off(LED_ID id) {
    CLEAR_BIT(PORTC, id);  // Use the CLEAR_BIT macro to turn off the LED
}

void LED_toggle(LED_ID id) {
    TOGGLE_BIT(PORTC, id);  // Use the TOGGLE_BIT macro to toggle the LED state
}


