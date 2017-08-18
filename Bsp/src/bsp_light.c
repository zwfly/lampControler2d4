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
	PWM_CLOCK_DIV_128;
	PWMPH = 0x03;
	PWMPL = 0xE8;
	/**********************************************************************
	 PWM frequency = Fpwm/((PWMPH,PWMPL) + 1) <Fpwm = Fsys/PWM_CLOCK_DIV>
	 = (16MHz/8)/(0x7CF + 1)
	 = 1KHz (1ms)
	 ***********************************************************************/

	PWM0H = 0x01;
	PWM0L = 0xF4;

//	set_SFRPAGE
//	;						//PWM4 and PWM5 duty seting is in SFP page 1
	PWM3H = 0x01;
	PWM3L = 0xD4;
	PWM5H = 0x01;
	PWM5L = 0xA4;
//	clr_SFRPAGE
//	;
	// PWM output inversly enable
//	PWM2_OUTPUT_INVERSE;

	//-------- PWM start run--------------
	set_LOAD;
	set_PWMRUN;

}
void Light_Red_set(uint8_t duty) {
	uint16_t d = 0;
	d = duty * 10;

	PWM5H = (d >> 8) & 0xFF;
	PWM5L = d & 0xFF;
}
void Light_Green_set(uint8_t duty) {
	uint16_t d = 0;
	d = duty * 10;

	PWM3H = (d >> 8) & 0xFF;
	PWM3L = d & 0xFF;
}
void Light_Blue_set(uint8_t duty) {
	uint16_t d = 0;
	d = duty * 10;

	PWM0H = (d >> 8) & 0xFF;
	PWM0L = d & 0xFF;
}

void Light_RGB_set(uint8_t r, uint8_t g, uint8_t b) {
	Light_Red_set(r);
	Light_Green_set(g);
	Light_Blue_set(b);
}
