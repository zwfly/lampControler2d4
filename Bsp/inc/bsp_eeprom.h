/*
 * bsp_eeprom.h
 *
 *  Created on: 2017Äê9ÔÂ8ÈÕ
 *      Author: fly
 */

#ifndef BSP_INC_BSP_EEPROM_H_
#define BSP_INC_BSP_EEPROM_H_

void EEPROM_InitHard(void);

void write_DATAFLASH_BYTE(UINT16 u16_addr, UINT8 u8_data);

UINT8 read_APROM_BYTE(UINT16 code *u16_addr);

#endif /* BSP_INC_BSP_EEPROM_H_ */
