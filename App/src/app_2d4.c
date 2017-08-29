/*
 * app_2d4.c
 *
 *  Created on: 2017年8月16日
 *      Author: fly
 */
#include "app.h"
#include <string.h>
#include <ctype.h>

static uint8_t sendRcv_flag = 0; //0 rcv， 1 send
static uint8_t rcvBuf[PAYLOAD_WIDTH] = { 0 };
static uint8_t sendBuf[PAYLOAD_WIDTH] = { 0 };

void app_2d4_init(void) {

	sendRcv_flag = 0;
	memset(rcvBuf, 0, sizeof(rcvBuf));
	memset(sendBuf, 0, sizeof(sendBuf));

	RF_Init();
	RF_RxMode();
//	RF_Carrier(1);

}

void app_2d4_send(uint8_t *d, uint8_t len) {
	if (len > sizeof(sendBuf)) {
		return;
	}

	RF_TxMode();
	sendRcv_flag = 1;

	if (sendBuf != d) {
		memset(sendBuf, 0, sizeof(sendBuf));
		memcpy(sendBuf, d, len);
	}
}
idata char sss[32] = { 0 };
static void app_2d4_Rcv(uint8_t *buf) {
	uint8_t i = 0;
	uint8_t index = 0;
	uint8_t check = 0;
#if 1
	sprintf(sss, "rcv %02X %02X %02X %02X %02X %02X\r\n", (uint16_t) buf[0],
			(uint16_t) buf[1], (uint16_t) buf[2], (uint16_t) buf[3],
			(uint16_t) buf[4], (uint16_t) buf[5]);
	printf(sss);
#endif
	if (buf[0] != LCD2LAMP_HEADER) {
		return;
	}
	if (buf[1] > sizeof(rcvBuf)) {
		return;
	}
	for (i = 0; i < (buf[1] + 1); i++) {
		check += buf[i + 1];
	}
	if (check != buf[buf[1] + 2]) {
		return;
	}

	memset(sendBuf, 0, sizeof(sendBuf));
	index = 0;
	switch (buf[2]) {
	case POWER_SHORT_CMD:

		printf("POWER_SHORT_CMD\r\n");
		break;
	case POWER_LONG_CMD:

		break;
	case ACC_CMD:

		if (buf[3] == 1) {
			Relay_on();
		} else if (buf[3] == 2) {
			Relay_off();
		} else if (buf[3] == 3) {
			Relay_toggle();
		}

		sendBuf[index++] = LAMP2LCD_HEADER;
		sendBuf[index++] = 0x02;
		sendBuf[index++] = buf[2];
		if (Relay_IsOn()) {
			sendBuf[index++] = 0x01;
		} else {
			sendBuf[index++] = 0x02;
		}
		for (i = 0; i < (sendBuf[1] + 1); i++) {
			sendBuf[index] += sendBuf[i + 1];
		}

		printf("ACC_CMD\r\n");
		break;
	case UP_CMD:

		printf("UP_CMD\r\n");
		break;
	case DOWN_CMD:

		printf("DOWN_CMD\r\n");
		break;
	case DOME_CMD:
		break;
	case VOL_ADD_CMD:

		printf("VOL_ADD_CMD\r\n");
		break;
	case VOL_MINUS_CMD:

		printf("VOL_MINUS_CMD\r\n");
		break;
	case PLAY_CMD:

		printf("PLAY_CMD\r\n");
		break;
	case MODE_CMD:

		printf("MODE_CMD\r\n");
		break;
	}
	if (index) {
		index++;
		app_2d4_send(sendBuf, index);
	}

}

void app_2d4_pro(void) {

	if (sendRcv_flag) {

		switch (ucRF_GetStatus()) {
		case TX_DS_FLAG: 		// 普通型发送完成 或 增强型发送成功

			RF_ClearFIFO();
			RF_ClearStatus();

			sendRcv_flag = 0;
			RF_RxMode();

			break;
		case RX_DR_FLAG:		//发送成功且收到payload

			RF_ClearFIFO();
			RF_ClearStatus();
			break;
		case MAX_RT_FLAG:		// 增强型发送超时失败

			RF_ClearFIFO();
			RF_ClearStatus();
			break;
		default:		// rf 处于空闲状态才发送数据

			RF_TxData(sendBuf, sizeof(sendBuf));
			sendRcv_flag = 0;
			break;
		}

	} else {
		if (ucRF_DumpRxData(rcvBuf, sizeof(rcvBuf))) {

			app_2d4_Rcv(rcvBuf);

		}
	}
}
