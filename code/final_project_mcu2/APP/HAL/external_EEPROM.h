/*
 * EEPROM.h
 *
 *  Created on: Oct 23, 2023
 *      Author: mario
 */

#ifndef EXTERNAL_EEPROM_H_
#define EXTERNAL_EEPROM_H_

#include"MCAL/std_types.h"

/****************************************************************************
 *                              Definitions
 ***************************************************************************/

#define SUCCESS 1
#define ERROR   0


/****************************************************************************
 *                            Functions prototype
 ***************************************************************************/

void EEPROM_init(void);

/*
 * NOTE:
 * you have 11-bit address : last address >> 0x07FF
 *
 * */
uint8 EEPROM_writeByte(uint16 u16add,uint8 u8data);
uint8 EEPROM_readByte(uint16 u16add,uint8* data);

#endif /* EXTERNAL_EEPROM_H_ */
