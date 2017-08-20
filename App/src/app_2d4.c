/*
 * app_2d4.c
 *
 *  Created on: 2017年8月16日
 *      Author: fly
 */
#include "app.h"
void app_2d4_init(void) {

	RF_Init();
//	RF_Carrier(1);

#if 0
	RF_RxMode();
#else
	RF_TxMode();
#endif
}
uint8_t n = 0;
void app_2d4_pro(void) {

	uint8_t ucPayload[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
#if 1
	//send data
	switch (ucRF_GetStatus()) {
	case TX_DS_FLAG: 		// 普通型发送完成 或 增强型发送成功
		//...
		if (n) {
			n = 0;
			Light_Green_set(1);
		} else {
			n = 1;
			Light_Green_set(90);
		}

		RF_ClearFIFO();
		RF_ClearStatus();
		break;
	case RX_DR_FLAG:		//发送成功且收到payload
		//...
		RF_ClearFIFO();
		RF_ClearStatus();
		break;
	case MAX_RT_FLAG:		// 增强型发送超时失败
		//...
		RF_ClearFIFO();
		RF_ClearStatus();
		break;
	default:		// rf 处于空闲状态才发送数据
		RF_TxData(ucPayload, PAYLOAD_WIDTH);
		break;

	}
#else
	if (ucRF_DumpRxData(ucPayload, PAYLOAD_WIDTH)) {
		//接收成功

		if (n) {
			n = 0;
			Light_Green_set(3);
		} else {
			n = 1;
			Light_Green_set(90);
		}

	}

#endif
}
