/*
 * ultrasonic.c
 *
 *  Created on: Oct 10, 2024
 *      Author: medha
 */

#include "ultrasonic.h"
#include <util/delay.h>

/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/

static volatile uint16 g_pulse_time = 0;

/*******************************************************************************
 *                      Function Definitions                                   *
 *******************************************************************************/

/* ICU Interrupt Service Routine Callback */
void Ultrasonic_EdgeProcessing(void) {
    static uint8 edge_flag = 0;

    if (edge_flag == 0) {
        // First edge (rising): Clear timer and change to detect falling edge
        ICU_clearTimerValue();
        ICU_setEdgeDetectionType(FALLING);
        edge_flag = 1;
    } else {
        // Second edge (falling): Capture the time and stop ICU
        g_pulse_time = ICU_getInputCaptureValue();
        ICU_setEdgeDetectionType(RAISING); // Prepare for the next measurement
        edge_flag = 0;
    }
}

/* Initialize the Ultrasonic sensor */
void Ultrasonic_Init(void) {
    // Configure Trigger pin as output
    GPIO_setupPinDirection(ULTRASONIC_TRIGGER_PORT, ULTRASONIC_TRIGGER_PIN, PIN_OUTPUT);

    // Initialize ICU to capture edge events from the Echo pin
    ICU_ConfigType icu_config = {F_CPU_8, RAISING};
    ICU_init(&icu_config);
    ICU_setCallBack(Ultrasonic_EdgeProcessing); // Set the callback for ICU ISR
}

/* Send the trigger pulse to start the measurement */
void Ultrasonic_Trigger(void) {
    GPIO_writePin(ULTRASONIC_TRIGGER_PORT, ULTRASONIC_TRIGGER_PIN, LOGIC_HIGH);
    _delay_us(10); // 10 µs pulse
    GPIO_writePin(ULTRASONIC_TRIGGER_PORT, ULTRASONIC_TRIGGER_PIN, LOGIC_LOW);
}

/* Read the distance measured by the ultrasonic sensor in centimeters */
uint16 Ultrasonic_ReadDistance(void) {
    uint16 distance = 0;

    // Trigger the sensor to start the measurement
    Ultrasonic_Trigger();

    // Wait until the measurement is completed (g_pulse_time is updated in ISR)
    while (g_pulse_time == 0);

    // Calculate the distance based on the pulse time (in timer ticks)
    distance = (g_pulse_time / 117.6) + 1;  // Formula as discussed earlier

    // Reset pulse_time for the next measurement
    g_pulse_time = 0;

    return distance;
}
