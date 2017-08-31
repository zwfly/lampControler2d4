/*
 * app_uart.c
 *
 *  Created on: 2017Äê8ÔÂ31ÈÕ
 *      Author: fly
 */

#include "app.h"
#include <string.h>

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

void app_uart_pro(void) {

	if (riflag) {
		riflag = 0;

		if ((rcv_T.pWrite + RCV_BUFSIZE - rcv_T.pRead) % RCV_BUFSIZE > 4) {

			if (((rcv_T.rxBuf[rcv_T.pRead]) == 0x55)
					&& ((rcv_T.rxBuf[(rcv_T.pRead + 1) % RCV_BUFSIZE]) == 0xAA)) {

				len = rcv_T.rxBuf[(rcv_T.pRead + 2) % RCV_BUFSIZE];

				if ((rcv_T.pWrite + RCV_BUFSIZE - rcv_T.pRead) % RCV_BUFSIZE
						>= (len + 4)) {

					if (rcv_T.rxBuf[(rcv_T.pRead + len + 3) % RCV_BUFSIZE]
							!= app_CalcCRC8_cycle(rcv_T.rxBuf + rcv_T.pRead,
									len + 3, rcv_T.pRead, RCV_BUFSIZE)) {
//						printf("check error\r\n");
						rcv_T.pRead++;

					} else {
						index = 0;
						memset(sendBuf,0,PAYLOAD_WIDTH);
						switch (rcv_T.rxBuf[(rcv_T.pRead + 3) % RCV_BUFSIZE]) {
						case VOL_ADD_UART_CMD:

							sendBuf[index++] = LAMP2LCD_HEADER;
							sendBuf[index++] = 0x02;
							sendBuf[index++] = VOL_ADD_CMD;
							sendBuf[index++] = rcv_T.rxBuf[(rcv_T.pRead + 4)
									% RCV_BUFSIZE];
							for (i = 0; i < (sendBuf[1] + 1); i++) {
								sendBuf[index] += sendBuf[i + 1];
							}
							index++;
							app_2d4_send(sendBuf, index);
							break;
						case VOL_MINUS_UART_CMD:

							sendBuf[index++] = LAMP2LCD_HEADER;
							sendBuf[index++] = 0x02;
							sendBuf[index++] = VOL_MINUS_CMD;
							sendBuf[index++] = rcv_T.rxBuf[(rcv_T.pRead + 4)
									% RCV_BUFSIZE];
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
