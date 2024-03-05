/*
 * keypad.h
 *
 *  Created on: Sep 25, 2023
 *      Author: mario
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include"MCAL/std_types.h"

/****************************************************************************
 *                               Definitions
 * *************************************************************************/

#define KEYPAD_NUM_OF_COLS  4
#define KEYPAD_NUM_OF_ROWS  4

#define KEYPAD_COL_PORT	PORTA_ID
#define KEYPAD_FIRST_COL_PIN 4

#define KEYPAD_ROW_PORT PORTA_ID
#define KEYPAD_FIRST_ROW_PIN 0

#define KEYPAD_PRESSED LOW
#define KEYPAD_RELEASED HIGH

/**************************************************************************
 *                          Functions prototype
 * *************************************************************************/

uint8 KEYPAD_getPressedKey(void);

#endif /* KEYPAD_H_ */
