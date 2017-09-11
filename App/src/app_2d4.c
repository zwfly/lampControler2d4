/*
 * app_2d4.c
 *
 *  Created on: 2017年8月16日
 *      Author: fly
 */
#include "app.h"
#include <string.h>
#include <ctype.h>

#include "app_2d4.h"

static uint8_t sendRcv_flag = 0; //0 rcv， 1 send
static uint8_t rcvBuf[PAYLOAD_WIDTH] = { 0 };
uint8_t sendBuf[PAYLOAD_WIDTH] = { 0 };

uint8_t tmpBuf[8] = { 0 };

//static uint8_t test_vol = 0;
//static uint8_t test_yinxiang_status = 0;

void app_2d4_init(void) {

	sendRcv_flag = 0;
	memset(rcvBuf, 0, sizeof(rcvBuf));
	memset(sendBuf, 0, sizeof(sendBuf));

	RF_Init();
#if 1

	RF_RxMode();
#else
	RF_TxMode();
	sendRcv_flag = 1;
#endif

//	RF_Carrier(1);

}

void app_2d4_send(uint8_t *d, uint8_t len) {
//	if (len > PAYLOAD_WIDTH) {
//		return;
//	}
	uint8_t i = 0;
	for (i = 0; i < 120; i++) {
		nop
		nop
		nop
		nop
	}
	RF_TxMode();
	sendRcv_flag = 1;

	for (i = 0; i < 120; i++) {
		nop
		nop
		nop
		nop
	}

	if (sendBuf != d) {
		memset(sendBuf, 0, PAYLOAD_WIDTH);
		memcpy(sendBuf, d, len);
	}

}
#if DEBUG
idata char sss[32] = {0};
#endif
static void app_2d4_Rcv(uint8_t *buf) {
	uint8_t tmp = 0;
	uint8_t i = 0;
	uint8_t index = 0;
	uint8_t check = 0;
#if DEBUG
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

	memset(sendBuf, 0, PAYLOAD_WIDTH);
	index = 0;
	switch (buf[2]) {
	case POWER_SHORT_CMD:

		if (g_tWork.status.bits.DOME) {
			g_tWork.status.bits.DOME = 0;

			sendBuf[index++] = LAMP2LCD_HEADER;
			sendBuf[index++] = 11;
			sendBuf[index++] = DOME_CMD;
			sendBuf[index++] = g_tWork.status.bits.DOME;
			sendBuf[index++] = g_tWork.status.bits.pause;
			app_dome_get_current_Name(sendBuf + index, 8);
			index += 8;
			for (i = 0; i < (sendBuf[1] + 1); i++) {
				sendBuf[index] += sendBuf[i + 1];
			}
			index++;
			app_2d4_send(sendBuf, index);
		}

#if DEBUG
		printf("POWER_SHORT_CMD\r\n");
#endif
		break;
	case POWER_LONG_CMD:
#if 0
		if (buf[3] == 1) {
			test_yinxiang_status = 1;
		} else if (buf[3] == 2) {
			test_yinxiang_status = 0;
		} else if (buf[3] == 3) {
			if (test_yinxiang_status) {
				test_yinxiang_status = 0;
			} else {
				test_yinxiang_status = 1;
			}
		}
		sendBuf[index++] = LAMP2LCD_HEADER;
		sendBuf[index++] = 0x02;
		sendBuf[index++] = buf[2];
		sendBuf[index++] = test_yinxiang_status;
		for (i = 0; i < (sendBuf[1] + 1); i++) {
			sendBuf[index] += sendBuf[i + 1];
		}
#else
		tmp = 0x03;
		app_uart_send(POWER_LONG_UART_CMD, &tmp, 1);

#endif

#if DEBUG
		printf("POWER_LONG_CMD\r\n");
#endif
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

#if DEBUG
		printf("ACC_CMD\r\n");
#endif
		break;
	case UP_CMD:
		if (g_tWork.status.bits.DOME) {

			if (g_tWork.status.bits.pause == 0) {

				app_dome_previous();
				sendBuf[index++] = LAMP2LCD_HEADER;
				sendBuf[index++] = 10;
				sendBuf[index++] = UP_CMD;
				sendBuf[index++] = 0x05;
				app_dome_get_current_Name(sendBuf + index, 8);
				index += 8;
				for (i = 0; i < (sendBuf[1] + 1); i++) {
					sendBuf[index] += sendBuf[i + 1];
				}
				index++;
				app_2d4_send(sendBuf, index);
			}
		} else {
			app_uart_send(UP_UART_CMD, 0, 0);
		}

#if DEBUG
		printf("UP_CMD\r\n");
#endif
		break;
	case DOWN_CMD:
		if (g_tWork.status.bits.DOME) {
			if (g_tWork.status.bits.pause == 0) {
				app_dome_next();
				sendBuf[index++] = LAMP2LCD_HEADER;
				sendBuf[index++] = 10;
				sendBuf[index++] = UP_CMD;
				sendBuf[index++] = 0x05;
				app_dome_get_current_Name(sendBuf + index, 8);
				index += 8;
				for (i = 0; i < (sendBuf[1] + 1); i++) {
					sendBuf[index] += sendBuf[i + 1];
				}
				index++;
				app_2d4_send(sendBuf, index);
			}
		} else {
			app_uart_send(DOWN_UART_CMD, 0, 0);
		}

#if DEBUG
		printf("DOWN_CMD\r\n");
#endif
		break;
	case DOME_CMD:

//		tmp = 0x03;
//		app_uart_send(DOME_UART_CMD, &tmp, 1);

		if (g_tWork.status.bits.DOME) {
			g_tWork.status.bits.DOME = 0;

		} else {
			g_tWork.status.bits.DOME = 1;
		}
		sendBuf[index++] = LAMP2LCD_HEADER;
		sendBuf[index++] = 11;
		sendBuf[index++] = DOME_CMD;
		sendBuf[index++] = g_tWork.status.bits.DOME;
		sendBuf[index++] = g_tWork.status.bits.pause;
		app_dome_get_current_Name(sendBuf + index, 8);
		index += 8;
		for (i = 0; i < (sendBuf[1] + 1); i++) {
			sendBuf[index] += sendBuf[i + 1];
		}
		index++;
		app_2d4_send(sendBuf, index);

		break;
	case VOL_ADD_CMD:
#if 0
		if (buf[3] == 1) {
			test_vol++;
			if (test_vol > 30) {
				test_vol = 30;
			}
		} else if (buf[3] == 2) {
			if (test_vol) {
				test_vol--;
			}
		}

		sendBuf[index++] = LAMP2LCD_HEADER;
		sendBuf[index++] = 0x02;
		sendBuf[index++] = buf[2];
		sendBuf[index++] = test_vol;
		for (i = 0; i < (sendBuf[1] + 1); i++) {
			sendBuf[index] += sendBuf[i + 1];
		}

#else

		app_uart_send(VOL_ADD_UART_CMD, 0, 0);

#endif

#if DEBUG
		printf("VOL_ADD_CMD\r\n");
#endif
		break;
	case VOL_MINUS_CMD:
#if 0
		if (buf[3] == 1) {
			test_vol++;
			if (test_vol > 30) {
				test_vol = 30;
			}
		} else if (buf[3] == 2) {
			if (test_vol) {
				test_vol--;
			}
		}

		sendBuf[index++] = LAMP2LCD_HEADER;
		sendBuf[index++] = 0x02;
		sendBuf[index++] = buf[2];
		sendBuf[index++] = test_vol;
		for (i = 0; i < (sendBuf[1] + 1); i++) {
			sendBuf[index] += sendBuf[i + 1];
		}
#else
		app_uart_send(VOL_MINUS_UART_CMD, 0, 0);
#endif

#if DEBUG
		printf("VOL_MINUS_CMD\r\n");
#endif
		break;
	case PLAY_CMD:
#if 0
		sendBuf[index++] = LAMP2LCD_HEADER;
		sendBuf[index++] = 0x03;
		sendBuf[index++] = buf[2];
		sendBuf[index++] = (uint8_t) g_tWork.mode;

		if (buf[3] == 3) {

			switch (g_tWork.mode) {
				case 'B':

				if (g_tWork.status.bits.BT) {
					g_tWork.status.bits.BT = 0;
				} else {
					g_tWork.status.bits.BT = 1;
				}
				sendBuf[index++] = g_tWork.status.bits.BT;
				break;
				case 'F':
				if (g_tWork.status.bits.FM) {
					g_tWork.status.bits.FM = 0;
				} else {
					g_tWork.status.bits.FM = 1;
				}
				sendBuf[index++] = g_tWork.status.bits.FM;
				break;
				case 'A':
				if (g_tWork.status.bits.AUX) {
					g_tWork.status.bits.AUX = 0;
				} else {
					g_tWork.status.bits.AUX = 1;
				}
				sendBuf[index++] = g_tWork.status.bits.AUX;
				break;
				case 'U':
				if (g_tWork.status.bits.USB) {
					g_tWork.status.bits.USB = 0;
				} else {
					g_tWork.status.bits.USB = 1;
				}
				sendBuf[index++] = g_tWork.status.bits.USB;
				break;
			}

		}

		for (i = 0; i < (sendBuf[1] + 1); i++) {
			sendBuf[index] += sendBuf[i + 1];
		}
#else
		if (g_tWork.status.bits.DOME) {
			if (g_tWork.status.bits.pause) {
				g_tWork.status.bits.pause = 0;
				app_dome_start_current();
			} else {
				g_tWork.status.bits.pause = 1;
				app_dome_stop_current();
			}

			sendBuf[index++] = LAMP2LCD_HEADER;
			sendBuf[index++] = 11;
			sendBuf[index++] = PLAY_CMD;
			sendBuf[index++] = 0x05;
			sendBuf[index++] = g_tWork.status.bits.pause;
			app_dome_get_current_Name(sendBuf + index, 8);
			index += 8;
			for (i = 0; i < (sendBuf[1] + 1); i++) {
				sendBuf[index] += sendBuf[i + 1];
			}
			index++;
			app_2d4_send(sendBuf, index);

		} else {
			app_uart_send(PLAY_UART_CMD, 0, 0);
		}

#endif
#if DEBUG
		printf("PLAY_CMD\r\n");
#endif
		break;
	case MODE_CMD:
#if 0
		if (buf[3] == 1) {
			switch (g_tWork.mode) {
				case 'B':
				g_tWork.mode = 'F';
				break;
				case 'F':
				g_tWork.mode = 'A';
				break;
				case 'A':
				g_tWork.mode = 'U';
				break;
				case 'U':
				g_tWork.mode = 'B';
				break;
			}
		}

		sendBuf[index++] = LAMP2LCD_HEADER;
		sendBuf[index++] = 0x02;
		sendBuf[index++] = buf[2];
		sendBuf[index++] = g_tWork.mode;
		for (i = 0; i < (sendBuf[1] + 1); i++) {
			sendBuf[index] += sendBuf[i + 1];
		}
#else
		app_uart_send(MODE_UART_CMD, 0, 0);
#endif

#if DEBUG
		printf("MODE_CMD\r\n");
#endif
		break;
	}
	if (index) {
		index++;
#if 0
		nop
		nop
		nop
		nop

		RF_TxMode();
		sendRcv_flag = 1;
		for (i = 0; i < 120; i++) {
			nop
			nop
			nop
			nop
		}
#else
		app_2d4_send(sendBuf, index);
#endif
	}

}

void app_2d4_pro(void) {

	if (sendRcv_flag) {

		switch (ucRF_GetStatus()) {
		case TX_DS_FLAG: 		// 普通型发送完成 或 增强型发送成功

			RF_ClearFIFO();
			RF_ClearStatus();

//			printf("Send OK\r\n");

			sendRcv_flag = 0;
			RF_RxMode();

//			Relay_toggle();

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

			break;
		}

	} else {
		if (ucRF_DumpRxData(rcvBuf, sizeof(rcvBuf))) {

			app_2d4_Rcv(rcvBuf);

		}
	}
}

