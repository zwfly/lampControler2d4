/*
 * bsp_relay.c
 *
 *  Created on: 2017Äê8ÔÂ18ÈÕ
 *      Author: fly
 */
#include "bsp.h"

void Relay_InitHard(void) {

	clr_P1M1_4;
	P1M2 |= SET_BIT4;

}
void Relay_on(void) {
	P04 = 1;
}
void Relay_off(void) {
	P04 = 0;
}
void Relay_set(uint8_t s) {
	if (s) {
		Relay_on();
	} else {
		Relay_off();
	}
}
