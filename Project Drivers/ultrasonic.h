/*
 * ultrasonic.h
 *
 *  Created on: Oct 10, 2024
 *      Author: medha
 */
#ifndef ULTRASONIC_SENSOR_H_
#define ULTRASONIC_SENSOR_H_

#include "std_types.h"
#include "gpio.h"
#include "icu.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define ULTRASONIC_TRIGGER_PORT PORTD_ID
#define ULTRASONIC_TRIGGER_PIN  PIN7_ID
#define ULTRASONIC_ECHO_PORT    PORTD_ID
#define ULTRASONIC_ECHO_PIN     PIN6_ID

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * Initialize the Ultrasonic sensor by setting up the ICU and configuring the Trigger pin.
 */
void Ultrasonic_Init(void);

/*
 * Description :
 * Send the trigger pulse to start the measurement.
 */
void Ultrasonic_Trigger(void);

/*
 * Description :
 * Get the distance measured by the ultrasonic sensor in centimeters.
 */
uint16 Ultrasonic_ReadDistance(void);

#endif /* ULTRASONIC_SENSOR_H_ */
