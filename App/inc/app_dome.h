/*
 * app_dome.h
 *
 *  Created on: 2017Äê9ÔÂ8ÈÕ
 *      Author: fly
 */

#ifndef APP_INC_APP_DOME_H_
#define APP_INC_APP_DOME_H_



typedef struct _COLOR_T {
	uint8_t R;
	uint8_t G;
	uint8_t B;
} COLOR_T;

typedef struct _SUBDOME_T {
	uint8_t mode;
	COLOR_T color1;
	COLOR_T color2;
	uint8_t repeate;
	uint16_t speed;
	uint8_t bright;
	uint16_t offtime;
} SUBDOME_T;
typedef struct _DOME_HEADER_T {
	char name[8];
	uint8_t number;

} DOME_HEADER_T;


void app_dome_interrupter(void);

#endif /* APP_INC_APP_DOME_H_ */
