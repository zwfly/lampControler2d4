#include "bsp.h"

BIT BIT_TMP;  //WTF

void bsp_Init(void) {

//	clr_BODEN;

//	Set_All_GPIO_Quasi_Mode();
//	Set_All_GPIO_Input_Mode();

	Wireless2d4_InitHard();

	Timer0_InitHard();
//	Timer1_InitHard();

//	Uart_InitHard();

	Light_InitHard();

	set_EA;         //enable interrupts

}

