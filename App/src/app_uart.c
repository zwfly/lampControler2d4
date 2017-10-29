/*
 * app_uart.c
 *
 *  Created on: 2017Äê8ÔÂ31ÈÕ
 *      Author: fly
 */

#include "app.h"
#include <string.h>

#define BT_MODE     0x01
#define FM_MODE     0x02
#define USB_MODE    0x03
#define AUX_MODE    0x04
#define DOME_MODE   0x05
#define CALL_MODE   0x06

static uint8_t index = 0;
static uint8_t len = 0;
static uint8_t i = 0;

static uint8_t uart_sendBuf[16] = { 0 };

void app_uart_Init(void) {
	index = 0;
	len = 0;
	i = 0;
}

void app_uart_send(uint8_t cmd, uint8_t *ptr, uint8_t len) {
	index = 0;

	uart_sendBuf[index++] = 0x55;
	uart_sendBuf[index++] = 0xAA;
	uart_sendBuf[index++] = len + 1;
	uart_sendBuf[index++] = cmd;
	for (i = 0; i < len; i++) {
		uart_sendBuf[index++] = *(ptr + i);
	}
	uart_sendBuf[index++] = app_CalcCRC8(uart_sendBuf, len + 4);

	for (i = 0; i < (len + 5); i++) {
		Send_Data_To_UART0(uart_sendBuf[i]);
	}
}
//idata char testBuf[64] = { 0 };
void app_uart_pro(void) {
	while (riflag) {
		riflag--;
		if ((rcv_T.pWrite + RCV_BUFSIZE - rcv_T.pRead) % RCV_BUFSIZE >= 4) {
			if (((rcv_T.rxBuf[rcv_T.pRead]) == 0x55)
					&& ((rcv_T.rxBuf[(rcv_T.pRead + 1) % RCV_BUFSIZE]) == 0xAA)) {
				len = rcv_T.rxBuf[(rcv_T.pRead + 2) % RCV_BUFSIZE];
				if ((rcv_T.pWrite + RCV_BUFSIZE - rcv_T.pRead) % RCV_BUFSIZE
						>= (len + 4)) {
					if (rcv_T.rxBuf[(rcv_T.pRead + len + 3) % RCV_BUFSIZE]
							!= app_CalcCRC8_cycle(rcv_T.rxBuf + rcv_T.pRead,
									len + 3, rcv_T.pRead, RCV_BUFSIZE)) {
//						printf("check error\r\n");
//						app_uart_send(0xFF, "check error\r\n",
//								strlen("check error\r\n"));

						rcv_T.pRead++;
					} else {
						index = 0;
						memset(sendBuf, 0, PAYLOAD_WIDTH);
						switch (rcv_T.rxBuf[(rcv_T.pRead + 3) % RCV_BUFSIZE]) {
						case RCV_VOL_CMD:
							sendBuf[index++] = LAMP2LCD_HEADER;
							sendBuf[index++] = len;
							sendBuf[index++] = RCV_VOL_CMD;
							sendBuf[index++] = rcv_T.rxBuf[(rcv_T.pRead + 4)
									% RCV_BUFSIZE];
							for (i = 0; i < (sendBuf[1] + 1); i++) {
								sendBuf[index] += sendBuf[i + 1];
							}
//							memset(testBuf, 0, 64);
//							sprintf(testBuf, "remain %d",
//									(uint16_t) ((rcv_T.pWrite + RCV_BUFSIZE
//											- rcv_T.pRead) % RCV_BUFSIZE));
//							app_uart_send(0xFF, testBuf, strlen(testBuf));
//							app_uart_send(0xFF, " hello\r\n", 7);
//							printf("RCV_VOL_CMD\r\n");
							index++;
							app_2d4_send(sendBuf, index);
							break;
						case RCV_POWER_STATUS_CMD:
							sendBuf[index++] = LAMP2LCD_HEADER;
							sendBuf[index++] = len;
							sendBuf[index++] = RCV_POWER_STATUS_CMD;
							sendBuf[index++] = rcv_T.rxBuf[(rcv_T.pRead + 4)
									% RCV_BUFSIZE];
							for (i = 0; i < (sendBuf[1] + 1); i++) {
								sendBuf[index] += sendBuf[i + 1];
							}
							index++;
							app_2d4_send(sendBuf, index);
							break;
						case RCV_X_BOX_STATUS_CMD:
							sendBuf[index++] = LAMP2LCD_HEADER;
							sendBuf[index++] = len;
							sendBuf[index++] = RCV_X_BOX_STATUS_CMD;
							sendBuf[index++] = rcv_T.rxBuf[(rcv_T.pRead + 4)
									% RCV_BUFSIZE];
							for (i = 0; i < (sendBuf[1] + 1); i++) {
								sendBuf[index] += sendBuf[i + 1];
							}
							index++;
							app_2d4_send(sendBuf, index);
							break;
						case RCV_BT_STATUS_CMD:
							sendBuf[index++] = LAMP2LCD_HEADER;
							sendBuf[index++] = len;
							sendBuf[index++] = RCV_BT_STATUS_CMD;
							sendBuf[index++] = rcv_T.rxBuf[(rcv_T.pRead + 4)
									% RCV_BUFSIZE];
							for (i = 0; i < (sendBuf[1] + 1); i++) {
								sendBuf[index] += sendBuf[i + 1];
							}
							index++;
							app_2d4_send(sendBuf, index);
							break;
						case RCV_PREV_NEXT_CMD:
							sendBuf[index++] = LAMP2LCD_HEADER;
							sendBuf[index++] = len;
							sendBuf[index++] = RCV_PREV_NEXT_CMD;
							sendBuf[index++] = rcv_T.rxBuf[(rcv_T.pRead + 4)
									% RCV_BUFSIZE];
							for (i = 0; i < (sendBuf[1] + 1); i++) {
								sendBuf[index] += sendBuf[i + 1];
							}
							index++;
							app_2d4_send(sendBuf, index);
							break;
						case RCV_USB_PLAY_TIME_CMD:
							sendBuf[index++] = LAMP2LCD_HEADER;
							sendBuf[index++] = len;
							sendBuf[index++] = RCV_USB_PLAY_TIME_CMD;
							sendBuf[index++] = rcv_T.rxBuf[(rcv_T.pRead + 4)
									% RCV_BUFSIZE];
							for (i = 0; i < (sendBuf[1] + 1); i++) {
								sendBuf[index] += sendBuf[i + 1];
							}
							index++;
							app_2d4_send(sendBuf, index);
							break;
						case RCV_FM_HZ_CMD:
							sendBuf[index++] = LAMP2LCD_HEADER;
							sendBuf[index++] = len;
							sendBuf[index++] = RCV_FM_HZ_CMD;
							sendBuf[index++] = rcv_T.rxBuf[(rcv_T.pRead + 4)
									% RCV_BUFSIZE];
							for (i = 0; i < (sendBuf[1] + 1); i++) {
								sendBuf[index] += sendBuf[i + 1];
							}
							index++;
							app_2d4_send(sendBuf, index);
							break;
						case MODE_CHANGE_CMD:   //MODE
							sendBuf[index++] = LAMP2LCD_HEADER;
							sendBuf[index++] = len;
							sendBuf[index++] = MODE_CHANGE_CMD;
							sendBuf[index++] = rcv_T.rxBuf[(rcv_T.pRead + 4)
									% RCV_BUFSIZE];
							switch (rcv_T.rxBuf[(rcv_T.pRead + 4) % RCV_BUFSIZE]) {
							case BT_MODE:  //BT
								sendBuf[index++] = rcv_T.rxBuf[(rcv_T.pRead + 5)
										% RCV_BUFSIZE];
								break;
							case FM_MODE:  //FM

								break;
							case AUX_MODE:  //AUX
								sendBuf[index++] = rcv_T.rxBuf[(rcv_T.pRead + 5)
										% RCV_BUFSIZE];
								break;
							case USB_MODE:  //USB

								break;
							default:
								break;
							}
							for (i = 0; i < (sendBuf[1] + 1); i++) {
								sendBuf[index] += sendBuf[i + 1];
							}
							index++;
							app_2d4_send(sendBuf, index);
							break;
						case RCV_PLAY_PAUSE_STATUS_CMD:
							sendBuf[index++] = LAMP2LCD_HEADER;
							sendBuf[index++] = len;
							sendBuf[index++] = RCV_PLAY_PAUSE_STATUS_CMD;
							sendBuf[index++] = rcv_T.rxBuf[(rcv_T.pRead + 4)
									% RCV_BUFSIZE];
							switch (rcv_T.rxBuf[(rcv_T.pRead + 4) % RCV_BUFSIZE]) {
							case BT_MODE:  //BT
								sendBuf[index++] = rcv_T.rxBuf[(rcv_T.pRead + 5)
										% RCV_BUFSIZE];
								break;
							case FM_MODE:  //FM
								sendBuf[index++] = rcv_T.rxBuf[(rcv_T.pRead + 5)
										% RCV_BUFSIZE];
								if (1
										== rcv_T.rxBuf[(rcv_T.pRead + 5)
												% RCV_BUFSIZE]) {
									sendBuf[index++] = rcv_T.rxBuf[(rcv_T.pRead
											+ 6) % RCV_BUFSIZE];
									sendBuf[index++] = rcv_T.rxBuf[(rcv_T.pRead
											+ 7) % RCV_BUFSIZE];
								}
								break;
							case AUX_MODE:  //AUX
								sendBuf[index++] = rcv_T.rxBuf[(rcv_T.pRead + 5)
										% RCV_BUFSIZE];
								break;
							case USB_MODE:  //USB
								sendBuf[index++] = rcv_T.rxBuf[(rcv_T.pRead + 5)
										% RCV_BUFSIZE];
								if (1
										== rcv_T.rxBuf[(rcv_T.pRead + 5)
												% RCV_BUFSIZE]) {
									sendBuf[index++] = rcv_T.rxBuf[(rcv_T.pRead
											+ 6) % RCV_BUFSIZE];
									sendBuf[index++] = rcv_T.rxBuf[(rcv_T.pRead
											+ 7) % RCV_BUFSIZE];
								}
								break;
							default:
								break;
							}

							for (i = 0; i < (sendBuf[1] + 1); i++) {
								sendBuf[index] += sendBuf[i + 1];
							}
							index++;
							app_2d4_send(sendBuf, index);

							break;
						default:
							break;
						}
						rcv_T.pRead += len + 4;
					}
				}
			} else {
				rcv_T.pRead++;
			}
			rcv_T.pRead = rcv_T.pRead % RCV_BUFSIZE;
		}
	}

}
