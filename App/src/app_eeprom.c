/*
 * app_eeprom.c
 *
 *  Created on: 2017Äê9ÔÂ8ÈÕ
 *      Author: fly
 */
#include "app.h"
#include <string.h>

void app_eeprom_Init(void) {

}

void app_eeprom_get_dome_with_index(DOME_DEFAULT_T *dd, uint8_t index) {
	uint8_t i = 0;
	uint8_t n = 0;
	n = index;

	if (n >= ((0x4800 - DOME_START_ADDR) / sizeof(DOME_DEFAULT_T))) {
		n = 0;
	}
	for (i = 0; i < sizeof(DOME_DEFAULT_T); i++) {
		*((uint8_t*) dd + i) = read_APROM_BYTE(
				(uint16_t*) (DOME_START_ADDR + index * sizeof(DOME_DEFAULT_T)
						+ i));
	}
} 
void app_eeprom_erase(uint16_t addr) {
	erase_DATAFLASH(DOME_START_ADDR + addr);
}
void app_eeprom_write_byte(uint16_t addr, uint8_t d) {
	write_DATAFLASH_BYTE(DOME_START_ADDR + addr, d);
}
void app_eeprom_write_buf(uint16_t addr, uint8_t *pt, uint8_t len) {
	write_DATAFLASH_BUF(DOME_START_ADDR + addr, pt, len);
}
uint8_t app_eeprom_read_byte(uint16_t addr) {
	return read_APROM_BYTE((uint16_t *)addr);
}
void app_eeprom_100ms_pro(void) {

}

static void app_eeprom_pro(void) {

}
