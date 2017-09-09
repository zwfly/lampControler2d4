/*
 * app_dome.c
 *
 *  Created on: 2017Äê9ÔÂ8ÈÕ
 *      Author: fly
 */

#include "app.h"

static SUBDOME_T subDome;
static uint8_t count = 0;
void app_dome_Init(void) {

}

void app_dome_1s_pro(void) {

}
void app_dome_500ms_pro(void) {

}
uint16_t app_dome_get_status(void) {

	return 0;
}
void app_dome_stop_current(void) {

}
void app_dome_start(uint8_t index) {

//	app_eeprom_get_dome_with_index(&subDome, index);

	count = subDome.repeate;
}
void app_dome_interrupter(void) {
	uint16_t cnt = 0;

//	(subDome.color1.R - subDome.color2.R);

}
