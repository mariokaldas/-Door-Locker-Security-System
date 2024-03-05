/*
 * buzzer.h
 *
 *  Created on: Oct 26, 2023
 *      Author: mario
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#include"MCAL/std_types.h"
#include"MCAL/gpio.h"


/****************************************************************************
 *                               Definitions
 ****************************************************************************/

#define BUZZER_PORT PORTA_ID
#define BUZZER_PIN 0

/****************************************************************************
 *                          Functions prototype
 ****************************************************************************/


void BUZZER_init(void);
void BUZZER_on(void);
void BUZZER_off(void);

#endif /* BUZZER_H_ */
