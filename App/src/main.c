#include "app.h"

static uint8_t dome_cnt = 0;

void main(void) {
	uint8_t ucKeyCode;

#if  0

//	set_HIRCEN
////	//step1: enable HIRC clock source run
//	while ((CKSWT & SET_BIT5) == 0)
//		;				//step2: check ready

	clr_HIRCEN

	set_EXTEN1
	set_EXTEN0

	clr_OSC1
//step3: switching system clock source if needed
	set_OSC0

	while ((CKEN & SET_BIT0) == 1)
	;//step4: check system clock switching OK or NG

#endif
	/****************/
	bsp_Init();

	/****************/
	app_eeprom_Init();
	app_2d4_init();
	app_work_Init();
	app_uart_Init();
	app_dome_Init();
	/****************/
//	Show_FW_Version_Number_To_PC();
	while (1) {

//		Relay_toggle();
		if (Task_time.flag_1ms) {
			Task_time.flag_1ms = 0;
			//////////////////

			dome_cnt++;
			if (dome_running_param.speed >= 50) {
				if (dome_cnt > (10 + (dome_running_param.speed - 50) / 3)) {
					dome_cnt = 0;
					app_dome_interrupter();
				}
			} else {
				if (dome_cnt > (10 - (50 - dome_running_param.speed) / 6)) {
					dome_cnt = 0;
					app_dome_interrupter();
				}
			}

		}

		if (Task_time.flag_10ms) {
			Task_time.flag_10ms = 0;
			//////////////////
			bsp_KeyScan();
//			app_dome_interrupter();

			app_uart_pro();
			app_2d4_pro();

		}
		if (Task_time.flag_100ms) {
			Task_time.flag_100ms = 0;
			//////////////////

//			app_work_100ms_pro();
//			Repeat_Pro();

		}
		if (Task_time.flag_500ms) {
			Task_time.flag_500ms = 0;
			//////////////////

		}
		if (Task_time.flag_1s) {
			Task_time.flag_1s = 0;
			//////////////////
#if DEBUG
			printf("I am alive\r\n");
#endif

			//		app_work_1s_pro();

		}
#if 1

		ucKeyCode = bsp_GetKey();
		if (ucKeyCode != KEY_NONE) {
			static uint8_t press_long_lock = 0;
			switch (ucKeyCode) {
			case KEY_UP_K1:   //
				if (press_long_lock == 0) {
//					g_tWork.status.bits.DEMO = 0;
//					app_dome_start_current();
					if (g_tWork.status.bits.blinkEnable) {
						uint8_t index = 0, i = 0;
						app_dome_next();
						sendBuf[index++] = LAMP2LCD_HEADER;
						sendBuf[index++] = 9;
						sendBuf[index++] = KEY_DOWN_CMD;
						app_dome_get_current_Name(sendBuf + index, 8);
						index += 8;
						for (i = 0; i < (sendBuf[1] + 1); i++) {
							sendBuf[index] += sendBuf[i + 1];
						}
						index++;
						app_2d4_send(sendBuf, index);
					}

				}
				press_long_lock = 0;
				break;
			case KEY_DOWN_K1:
				break;
			case KEY_LONG_K1:
				press_long_lock = 1;
				if (g_tWork.status.bits.blinkEnable) {
					g_tWork.status.bits.blinkEnable = 0;
//					g_tWork.status.bits.DEMO = 0;
					app_dome_stop_current();
				} else {
					g_tWork.status.bits.blinkEnable = 1;
					g_tWork.status.bits.DEMO = 0;
//					app_dome_start(0, 0);
					app_dome_start_current();
				}
				break;
			case KEY_UP_K2:   //
				break;
			case KEY_DOWN_K2: {
//				uint8_t index = 0, i = 0;
				Relay_toggle();

#if 0
				sendBuf[index++] = LAMP2LCD_HEADER;
				sendBuf[index++] = 0x02;
				sendBuf[index++] = KEY_ACC_CMD;
				if (Relay_IsOn()) {
					sendBuf[index++] = 0x01;
				} else {
					sendBuf[index++] = 0x02;
				}
				for (i = 0; i < (sendBuf[1] + 1); i++) {
					sendBuf[index] += sendBuf[i + 1];
				}
				index++;
				app_2d4_send(sendBuf, index);
#endif
			}

				break;
			case KEY_LONG_K2:
				break;
			}
		}
#endif
	}
}
