/*
 * DCmotor.h
 *
 *  Created on: Oct 13, 2023
 *      Author: mario
 */

#ifndef DCMOTOR_H_
#define DCMOTOR_H_

#include"MCAL/std_types.h"
/***************************************************************************
 *                             Definitions
 * *************************************************************************/
#define IN1_PORT PORTB_ID
#define IN1_PIN 5

#define IN2_PORT PORTB_ID
#define IN2_PIN 4

#define EN_PORT PORTB_ID
#define EN_PIN 3

/*************************************************************************
 *                           Types declaration
 * ***********************************************************************/

typedef enum{
	CW,A_CW,STOP_MOTOR
}DCmotor_state;

/************************************************************************
 *                          Functions prototype
 * ***********************************************************************/

void DCmotor_init(void);
void DCmotor_rotate(DCmotor_state state,uint8 speed);

#endif /* DCMOTOR_H_ */
