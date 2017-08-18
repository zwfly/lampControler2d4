#include "app.h"

//uint8_t c;
//DEVICE_T g_tDevice;
/******************************************************************************
 * FUNCTION_PURPOSE: ADC interrupt Service Routine
 ******************************************************************************/
void ADC_ISR(void) interrupt 11
{
	clr_ADCF;                               //clear ADC interrupt flag
}
/******************************************************************************
 * FUNCTION_PURPOSE: I/O Pin interrupt Service Routine
 ******************************************************************************/
void PinInterrupt_ISR(void)
interrupt 7
{


	PIF = 0x00;                             //clear interrupt flag
}
void main(void) {

#if  0
	CKDIV = 1;                        //Fsys = Fosc / (2* CLKDIV) = Fcpu
#endif

	/****************/
	bsp_Init();

	/****************/
	app_2d4_init();
//	work_Init();


	/****************/
//	Show_FW_Version_Number_To_PC();

	while (1) {

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
		if (Task_time.flag_1s) {
			static uint8_t tmp = 0;
			static uint8_t cnt = 0;
			Task_time.flag_1s = 0;
			//////////////////

//			app_work_1s_pro();


		
			cnt++;
			if (cnt > 3) {
				cnt = 10;

				tmp++;
//				LCD_Show_REP_Num(tmp % 99);
//				LCD_Show_Pulls_Num(tmp);
//				LCD_Show_CAL_Num(tmp);
			}


		}

	}
}
