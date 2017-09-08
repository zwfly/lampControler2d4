#include "app.h"

uint8_t dd = 0;

void main(void) {

	/****************/
	bsp_Init();

	/****************/
	app_eeprom_Init();
	app_2d4_init();
	app_work_Init();
	app_uart_Init();
	/****************/
//	Show_FW_Version_Number_To_PC();
	while (1) {

		app_uart_pro();

		if (Task_time.flag_10ms) {
			Task_time.flag_10ms = 0;
			//////////////////

		}
		if (Task_time.flag_100ms) {
			Task_time.flag_100ms = 0;
			//////////////////
			app_2d4_pro();
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

//			app_work_1s_pro();

		}
	}
}
