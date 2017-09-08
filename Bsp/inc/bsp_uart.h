/*
 * bsp_uart.h
 *
 *  Created on: 2017��6��27��
 *      Author: fly
 */

#ifndef BSP_INC_BSP_UART_H_
#define BSP_INC_BSP_UART_H_

#define RCV_BUFSIZE  128

typedef struct _RCV_T {

	uint8_t rxBuf[RCV_BUFSIZE];
	uint8_t pWrite;
	uint8_t pRead;

} RCV_T;

extern idata RCV_T rcv_T;
extern BIT riflag;

void Uart_InitHard(void);

#endif /* BSP_INC_BSP_UART_H_ */
