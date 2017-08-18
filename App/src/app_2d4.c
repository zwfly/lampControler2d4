/*
 * app_2d4.c
 *
 *  Created on: 2017��8��16��
 *      Author: fly
 */
#include "app.h"
void app_2d4_init(void) {

}

void app_2d4_pro(void) {

	uint8_t ucPayload[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };

	//send data
	switch (ucRF_GetStatus()) {
	case TX_DS_FLAG: 		// ��ͨ�ͷ������ �� ��ǿ�ͷ��ͳɹ�
		//...
		RF_ClearFIFO();
		RF_ClearStatus();
		break;
	case RX_TX_FLAG:		//���ͳɹ����յ�payload
		//...
		RF_ClearFIFO();
		RF_ClearStatus();
		break;
	case MAX_RT_FLAG:		// ��ǿ�ͷ��ͳ�ʱʧ��
		//...
		RF_ClearFIFO();
		RF_ClearStatus();
		break;
	default:			// rf ���ڿ���״̬�ŷ�������
		RF_TxData(ucPayload, PAYLOAD_WIDTH);
		break;

	}
/////////
	if (ucRF_DumpRxData(ucPayload, PAYLOAD_WIDTH)) {
		//���ճɹ�
	}
}
