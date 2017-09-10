/*
 * bsp_light.c
 *
 *  Created on: 2017Äê8ÔÂ18ÈÕ
 *      Author: fly
 */

#include "bsp.h"

void Light_InitHard(void) {

	clr_P0M1_3;
	set_P0M2_3;

	clr_P0M1_4;
	set_P0M2_4;

	clr_P1M1_2;
	P1M2 |= SET_BIT2;
//	set_P1M2_2;

	PWM0_P12_OUTPUT_ENABLE;
	PWM3_P04_OUTPUT_ENABLE
	;
	PWM5_P03_OUTPUT_ENABLE;

	PWM_IMDEPENDENT_MODE;
	PWM_CLOCK_DIV_2
	;
	PWMPH = 0xFF;
	PWMPL = 0xFF;
	/**********************************************************************
	 PWM frequency = Fpwm/((PWMPH,PWMPL) + 1) <Fpwm = Fsys/PWM_CLOCK_DIV>
	 = (16MHz/8)/(0x7CF + 1)
	 = 1KHz (1ms)
	 ***********************************************************************/

//	PWM0H = 0x01;
//	PWM0L = 0xF4;
//	set_SFRPAGE
//	;						//PWM4 and PWM5 duty seting is in SFP page 1
//	PWM3H = 0x01;
//	PWM3L = 0xD4;
//	PWM5H = 0x01;
//	PWM5L = 0xA4;
//	clr_SFRPAGE
//	;
	// PWM output inversly enable
//	PWM2_OUTPUT_INVERSE;
	//-------- PWM start run--------------
//	set_LOAD;
	set_PWMRUN;

	Light_RGB_set(0, 0, 0);
}
void Light_Red_set(uint16_t duty) {
	set_SFRPAGE
	;
	PWM5H = (duty >> 8) & 0xFF;
	PWM5L = duty & 0xFF;
	clr_SFRPAGE
	;
	set_LOAD;
}
void Light_Green_set(uint16_t duty) {
	PWM3H = (duty >> 8) & 0xFF;
	PWM3L = duty & 0xFF;
	set_LOAD;
}
void Light_Blue_set(uint16_t duty) {
	PWM0H = (duty >> 8) & 0xFF;
	PWM0L = duty & 0xFF;
	set_LOAD;
}

void Light_RGB_set(uint16_t r, uint16_t g, uint16_t b) {
	Light_Red_set(r);
	Light_Green_set(g);
	Light_Blue_set(b);
}
