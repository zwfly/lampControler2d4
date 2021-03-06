/*
 * app_uart.c
 *
 *  Created on: 2017��8��31��
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
static uint8_t i = 0, j = 0;
static uint16_t tmp = 0;
static uint8_t u8_tmp = 0;
static uint8_t uart_sendBuf[16] = { 0 };

void app_uart_Init(void) {
	index = 0;
	len = 0;
	i = 0;

	memset((uint8_t *) &rcv_T, 0, sizeof(RCV_T));
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
						rcv_T.pRead++;
					} else {
						index = 0;
						memset(sendBuf, 0, PAYLOAD_WIDTH);
						switch (rcv_T.rxBuf[(rcv_T.pRead + 3) % RCV_BUFSIZE]) {
						case BLINK_METHOD_CMD:  //����
						{
							uint16_t index = 0;
							index =
									rcv_T.rxBuf[(rcv_T.pRead + 12) % RCV_BUFSIZE];
							u8_tmp = (0x4800 - DOME_START_ADDR)
									/ sizeof(DOME_DEFAULT_T);
							if (index >= (u8_tmp - 1)) {
								break;
							}
							u8_tmp = (0x4800 - DOME_START_ADDR) / 128;
							if (index == 0) {
								for (i = 0; i < u8_tmp; i++) {
									app_eeprom_erase(i * 128);
								}
							}
#if 0
							for (i = (index + 1); i < DEFAULT_DOME_NUM; i++) {
								uint16_t addr = i * sizeof(DOME_DEFAULT_T)
								+ (&dome_blink.header.index
										- &dome_blink);
								app_eeprom_write_byte(addr, 0);
								nop
							}
#endif
#if 1
							tmp = rcv_T.rxBuf[(rcv_T.pRead + 13) % RCV_BUFSIZE]
									& 0x0F;
							for (i = 0;
									i
											< (tmp * sizeof(SUBDOME_T)
													+ sizeof(DOME_HEADER_T));
									i++) {
								uint16_t addr = index * sizeof(DOME_DEFAULT_T)
										+ i;
								app_eeprom_write_byte(addr,
										rcv_T.rxBuf[(rcv_T.pRead + 4 + i)
												% RCV_BUFSIZE]);
							}

#endif

#if 0
							u8_tmp = (0x4800 - DOME_START_ADDR)
							/ sizeof(DOME_DEFAULT_T);
							blink_number = 0;
							for (i = 0; i < u8_tmp; i++) {
								if (0xFF != app_eeprom_read_byte(
												DOME_START_ADDR + i * sizeof(DOME_DEFAULT_T))) {
									blink_number++;
								} else {
									break;
								}
							}
#endif
							u8_tmp = index & 0xFF;
							app_uart_send(BLINK_METHOD_CMD, &u8_tmp, 1);
						}
							break;
						case RCV_VOL_CMD:
							sendBuf[index++] = LAMP2LCD_HEADER;
							sendBuf[index++] = len;
							sendBuf[index++] = RCV_VOL_CMD;
							for (i = 0; i < (len - 1); i++) {
								sendBuf[index++] = rcv_T.rxBuf[(rcv_T.pRead + 4
										+ i) % RCV_BUFSIZE];
							}
							for (i = 0; i < (sendBuf[1] + 1); i++) {
								sendBuf[index] += sendBuf[i + 1];
							}
							index++;
							app_2d4_send(sendBuf, index);
							break;
						case RCV_POWER_STATUS_CMD:
							sendBuf[index++] = LAMP2LCD_HEADER;
							sendBuf[index++] = len;
							sendBuf[index++] = RCV_POWER_STATUS_CMD;
							for (i = 0; i < (len - 1); i++) {
								sendBuf[index++] = rcv_T.rxBuf[(rcv_T.pRead + 4
										+ i) % RCV_BUFSIZE];
							}
							for (i = 0; i < (sendBuf[1] + 1); i++) {
								sendBuf[index] += sendBuf[i + 1];
							}
							index++;
							app_2d4_send(sendBuf, index);
							break;
#if 0
							case RCV_X_BOX_STATUS_CMD:
							sendBuf[index++] = LAMP2LCD_HEADER;
							sendBuf[index++] = len;
							sendBuf[index++] = RCV_X_BOX_STATUS_CMD;
							for (i = 0; i < (len - 1); i++) {
								sendBuf[index++] = rcv_T.rxBuf[(rcv_T.pRead + 4
										+ i) % RCV_BUFSIZE];
							}
							for (i = 0; i < (sendBuf[1] + 1); i++) {
								sendBuf[index] += sendBuf[i + 1];
							}
							index++;
							app_2d4_send(sendBuf, index);
							break;
#endif
						case RCV_BT_STATUS_CMD:
							if (g_tWork.status.bits.DOME) {
								break;
							}
							sendBuf[index++] = LAMP2LCD_HEADER;
							sendBuf[index++] = len;
							sendBuf[index++] = RCV_BT_STATUS_CMD;
							for (i = 0; i < (len - 1); i++) {
								sendBuf[index++] = rcv_T.rxBuf[(rcv_T.pRead + 4
										+ i) % RCV_BUFSIZE];
							}
							for (i = 0; i < (sendBuf[1] + 1); i++) {
								sendBuf[index] += sendBuf[i + 1];
							}
							index++;
							app_2d4_send(sendBuf, index);
							break;
						case RCV_PREV_NEXT_CMD:
							if (g_tWork.status.bits.DOME) {
								break;
							}
							sendBuf[index++] = LAMP2LCD_HEADER;
							sendBuf[index++] = len;
							sendBuf[index++] = RCV_PREV_NEXT_CMD;
							for (i = 0; i < (len - 1); i++) {
								sendBuf[index++] = rcv_T.rxBuf[(rcv_T.pRead + 4
										+ i) % RCV_BUFSIZE];
							}
							for (i = 0; i < (sendBuf[1] + 1); i++) {
								sendBuf[index] += sendBuf[i + 1];
							}
							index++;
							app_2d4_send(sendBuf, index);
							break;
						case RCV_USB_PLAY_TIME_CMD:
							if (g_tWork.status.bits.DOME) {
								break;
							}
							sendBuf[index++] = LAMP2LCD_HEADER;
							sendBuf[index++] = len;
							sendBuf[index++] = RCV_USB_PLAY_TIME_CMD;
							for (i = 0; i < (len - 1); i++) {
								sendBuf[index++] = rcv_T.rxBuf[(rcv_T.pRead + 4
										+ i) % RCV_BUFSIZE];
							}
							for (i = 0; i < (sendBuf[1] + 1); i++) {
								sendBuf[index] += sendBuf[i + 1];
							}
							index++;
							app_2d4_send(sendBuf, index);
							break;
						case RCV_FM_HZ_CMD:
							if (g_tWork.status.bits.DOME) {
								break;
							}
							sendBuf[index++] = LAMP2LCD_HEADER;
							sendBuf[index++] = len;
							sendBuf[index++] = RCV_FM_HZ_CMD;
							for (i = 0; i < (len - 1); i++) {
								sendBuf[index++] = rcv_T.rxBuf[(rcv_T.pRead + 4
										+ i) % RCV_BUFSIZE];
							}
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
							for (i = 0; i < (len - 1); i++) {
								sendBuf[index++] = rcv_T.rxBuf[(rcv_T.pRead + 4
										+ i) % RCV_BUFSIZE];
							}
							for (i = 0; i < (sendBuf[1] + 1); i++) {
								sendBuf[index] += sendBuf[i + 1];
							}
							index++;
							app_2d4_send(sendBuf, index);
							break;
						case RCV_PLAY_PAUSE_STATUS_CMD:
							if (g_tWork.status.bits.DOME) {
								break;
							}
							sendBuf[index++] = LAMP2LCD_HEADER;
							sendBuf[index++] = len;
							sendBuf[index++] =
							RCV_PLAY_PAUSE_STATUS_CMD;
							for (i = 0; i < (len - 1); i++) {
								sendBuf[index++] = rcv_T.rxBuf[(rcv_T.pRead + 4
										+ i) % RCV_BUFSIZE];
							}
							for (i = 0; i < (sendBuf[1] + 1); i++) {
								sendBuf[index] += sendBuf[i + 1];
							}
							index++;
							app_2d4_send(sendBuf, index);

							break;
						case DEVICE_STA_CMD: {
							uint8_t sta[2] = 0;
							memset(sta, 0, sizeof(sta));
							sta[0] |=
									g_tWork.status.bits.blinkEnable ? 0x80 : 0;
							sta[0] |= g_tWork.status.bits.DEMO ? 0x40 : 0;
							sta[1] |= Relay_IsOn() ? 0x01 : 0;
							app_uart_send(DEVICE_STA_CMD, sta, sizeof(sta));
						}
							break;
							/// app --start
						case KEY_CARD_POWER_CMD:
							if (g_tWork.status.bits.blinkEnable == 0) {
								g_tWork.status.bits.blinkEnable = 1;
								app_dome_start_current();
							} else {
								g_tWork.status.bits.blinkEnable = 0;
								app_dome_stop_current();
							}
							sendBuf[index++] = LAMP2LCD_HEADER;
							sendBuf[index++] = 10;
							sendBuf[index++] = KEY_POWER_SHORT_CMD;
							if (g_tWork.status.bits.blinkEnable) {
								sendBuf[index++] = 0;
							} else {
								sendBuf[index++] = 1;
							}
							app_dome_get_current_Name(sendBuf + index, 8);
#if 1
							for (i = 0; i < 8; i++) {
								if ((*(sendBuf + index + i) == 0)
										|| (*(sendBuf + index + i) == 0xFF)) {
									*(sendBuf + index + i) = ' ';
								}
							}
#endif
							index += 8;
							for (i = 0; i < (sendBuf[1] + 1); i++) {
								sendBuf[index] += sendBuf[i + 1];
							}
							index++;
							app_2d4_send(sendBuf, index);
							break;
						case KEY_CARD_DEMO_CMD:
//							if (g_tWork.status.bits.DEMO) {
//								g_tWork.status.bits.DEMO = 0;
//							} else {
							g_tWork.status.bits.DEMO = 1;
//							}
							app_dome_start(0);

							break;
						case APP_COLOR_ATLA_CMD:
#if 1
							app_dome_rgb(
									rcv_T.rxBuf[(rcv_T.pRead + 4) % RCV_BUFSIZE],
									rcv_T.rxBuf[(rcv_T.pRead + 5) % RCV_BUFSIZE],
									rcv_T.rxBuf[(rcv_T.pRead + 6) % RCV_BUFSIZE]);
#else
							app_dome_rgb(0xFFFF, 0xFFFF, 0xFFFF);
#endif
							break;
						case APP_BRIGHT_CMD:
							dome_running_param.bright = rcv_T.rxBuf[(rcv_T.pRead
									+ 4) % RCV_BUFSIZE];
							Light_bright_set(
									rcv_T.rxBuf[(rcv_T.pRead + 4) % RCV_BUFSIZE]);
							break;
						case APP_SPEED_CMD:
							dome_running_param.speed = rcv_T.rxBuf[(rcv_T.pRead
									+ 4) % RCV_BUFSIZE];
							break;
						case APP_FLASH_INDEX_CMD:
							g_tWork.status.bits.DEMO = 0;
							g_tWork.status.bits.blinkEnable = 1;
							app_dome_start(
									rcv_T.rxBuf[(rcv_T.pRead + 4) % RCV_BUFSIZE]);
							break;
						case APP_SWITCH_INDEX_CMD: {
							uint8_t switchData = rcv_T.rxBuf[(rcv_T.pRead + 4)
									% RCV_BUFSIZE];
							if (((switchData >> 4) & 0x0F) == 0) {
								Relay_set(switchData & 0x0F);
							}
						}
							break;
							/// app --end
						default:
							break;
						}
						rcv_T.pRead += len + 4;
#if 1
						rcv_T.pRead = rcv_T.pRead % RCV_BUFSIZE;
//						break;
						return;
#endif
					}
				}
			} else {
				rcv_T.pRead++;
			}
			rcv_T.pRead = rcv_T.pRead % RCV_BUFSIZE;
		}
	}

}
