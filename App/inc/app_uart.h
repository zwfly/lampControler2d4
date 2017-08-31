/*
 * app_uart.h
 *
 *  Created on: 2017��8��31��
 *      Author: fly
 */

#ifndef APP_INC_APP_UART_H_
#define APP_INC_APP_UART_H_

#define VOL_ADD_UART_CMD      0x36
#define VOL_MINUS_UART_CMD    0x37






void app_uart_Init(void);
void app_uart_send(uint8_t cmd, uint8_t *ptr, uint8_t len) ;
void app_uart_pro(void);

#endif /* APP_INC_APP_UART_H_ */
