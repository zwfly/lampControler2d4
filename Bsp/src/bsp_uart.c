/*
 * bsp_uart.c
 *
 *  Created on: 2017Äê6ÔÂ27ÈÕ
 *      Author: fly
 */

#include "bsp.h"

idata RCV_T rcv_T;

BIT riflag = 0;

void Uart_InitHard(void) {
	riflag = 0;
	InitialUART0_Timer1(9600);
}

void SerialPort0_ISR(void)
interrupt 4
{
	if (RI == 1) { /* if reception occur */
		clr_RI; /* clear reception flag for next reception */
		rcv_T.rxBuf[rcv_T.pWrite++] = SBUF;
		if (rcv_T.pWrite >= RCV_BUFSIZE) {
			rcv_T.pWrite = 0;
		}
		riflag = 1;

	}
	if (TI == 1) {
		clr_TI; /* if emission occur */
	}
}

