/*
 * main.c
 *
 *  Created on: Oct 10, 2024
 *      Author: medha
 */

#include "lcd.h"
#include "buzzer.h"
#include "ultrasonic.h"
#include "gpio.h"
#include <util/delay.h>
#include "led.h"
#include <avr/io.h>

#define DISTANCE_ALERT 5
#define DISTANCE_YELLOW 10
#define DISTANCE_GREEN 15
#define DISTANCE_RED 20

void LED_control(uint16 distance) {
    if (distance <= DISTANCE_ALERT) {
        LED_toggle(LED_BLUE);
        LED_toggle(LED_GREEN);
        LED_toggle(LED_RED);
        Buzzer_on();
    }
    else if (distance <= DISTANCE_YELLOW) {
        LED_on(LED_BLUE);
        LED_on(LED_GREEN);
        LED_on(LED_RED);
        Buzzer_off();
    }
    else if (distance <= DISTANCE_GREEN) {
        LED_off(LED_BLUE);
        LED_on(LED_GREEN);
        LED_on(LED_RED);
        Buzzer_off();
    }
    else if (distance <= DISTANCE_RED) {
        LED_off(LED_BLUE);
        LED_off(LED_GREEN);
        LED_on(LED_RED);
        Buzzer_off();
    } else {
        LED_off(LED_BLUE);
        LED_off(LED_GREEN);
        LED_off(LED_RED);
        Buzzer_off();
    }
}

int main(void) {
    // Initialize the system components
    LCD_init();
    Ultrasonic_Init();
    Buzzer_init();
    LEDS_init();
    SREG |= (1<<7); // Enable global interrupts

    uint16 distance = 0;
    LCD_displayString("Distance=  CM");

    while (1) {
        // Read distance from ultrasonic sensor
        distance = Ultrasonic_ReadDistance();
        LCD_moveCursor(0, 9);

        // Display the distance on the LCD
        if (distance >= 10) {
            LCD_intgerToString(distance);
        } else {
            LCD_intgerToString(distance);
            LCD_displayCharacter(' '); // Clear trailing digits
        }

        // Control the LEDs and buzzer based on distance
        LED_control(distance);

        // Display "STOP!" when distance is too close
        if (distance <= DISTANCE_ALERT) {
            LCD_displayStringRowColumn(1, 5, "STOP!");
        } else {
            LCD_displayStringRowColumn(1, 5, "     "); // Clear message
        }

        _delay_ms(200); // Small delay to stabilize sensor readings
    }
}
