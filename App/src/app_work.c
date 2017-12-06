/*
 * app_work.c
 *
 *  Created on: 2017Äê7ÔÂ6ÈÕ
 *      Author: admin
 */

#include "app.h"

WORK_T g_tWork;

void app_work_Init(void) {

//	g_tWork.mode = 'B';

}

void app_work_1s_pro(void) {
	static uint8_t cnt = 0;
	uint8_t index = 0, i = 0;

	cnt++;
	if (cnt >= 2) {
		cnt = 0;
		index = 0;
		sendBuf[index++] = LAMP2LCD_HEADER;
		sendBuf[index++] = 0x01;
		sendBuf[index++] = DEVICE_HEART_CMD;
		for (i = 0; i < (sendBuf[1] + 1); i++) {
			sendBuf[index] += sendBuf[i + 1];
		}
		index++;
		app_2d4_send(sendBuf, index);
	}

}
void app_work_100ms_pro(void) {

}

static void app_work_pro(void) {

}

