/*
 * app_dome.c
 *
 *  Created on: 2017Äê9ÔÂ8ÈÕ
 *      Author: fly
 */

#include "app.h"
#include <stdlib.h>

static SUBDOME_T subDome;
static DOME_HEADER_T domeHeader;
static SUBDOME_ASSIST_T subDome_Assist;

code const DOME_DEFAULT_T dome_default[DEFAULT_DOME_NUM] = {  //
		{ //start big dome0
				{  //start header0
						"HOME", 3  //header0 body
						},//end header0
						{  //start dome0

						{ 0x04, { 0, 0, 255 }, { 0, 0, 0 }, 1, 200, 100, 0 }, //subdome0
								{ 0x04, { 255, 0, 0 }, { 0, 0, 0 }, 1, 200, 100,
										0 },  //subdome1
								{ 0x04, { 0, 255, 0 }, { 0, 0, 0 }, 1, 200, 100,
										0 },  //subdome2
								{ 0x04, { 0, 255, 0 }, { 0, 0, 0 }, 1, 200, 100,
										0 },   //subdome3
								{ 0x04, { 0, 255, 0 }, { 0, 0, 0 }, 1, 200, 100,
										0 },  //subdome4
								{ 0x04, { 0, 255, 0 }, { 0, 0, 0 }, 1, 200, 100,
										0 },  //subdome5
								{ 0x04, { 0, 255, 0 }, { 0, 0, 0 }, 1, 200, 100,
										0 },  //subdome6
								{ 0x04, { 0, 255, 0 }, { 0, 0, 0 }, 1, 200, 100,
										0 }    //subdome7
						}  //end dome0
				},  // end big dome0
				{ //start big dome1
				{  //start header0
						"FOO", 3 }, //end header0
						{  //start dome0
						{ 0x04, { 255, 0, 0 }, { 0, 0, 0 }, 1, 200, 100, 0 }, //subdome0
								{ 0x04, { 0, 255, 0 }, { 0, 0, 0 }, 1, 200, 100,
										0 },  //subdome1
								{ 0x04, { 0, 0, 255 }, { 0, 0, 0 }, 1, 200, 100,
										0 },  //subdome2
								{ 0x04, { 0, 0, 255 }, { 0, 0, 0 }, 1, 200, 100,
										0 },   //subdome3
								{ 0x04, { 0, 0, 255 }, { 0, 0, 0 }, 1, 200, 100,
										0 },  //subdome4
								{ 0x04, { 0, 0, 255 }, { 0, 0, 0 }, 1, 200, 100,
										0 },  //subdome5
								{ 0x04, { 0, 0, 255 }, { 0, 0, 0 }, 1, 200, 100,
										0 },  //subdome6
								{ 0x04, { 0, 0, 255 }, { 0, 0, 0 }, 1, 200, 100,
										0 }    //subdome7

						}  //end dome0
				},  // end big dome1
				{ //start big dome0
				{  //start header0
						"BAR", 1 }, //end header0
						{  //start dome0
						{ 0x04, { 0, 0, 255 }, { 0, 0, 0 }, 4, 200, 100, 0 }, //subdome0
								{ 0x04, { 0, 0, 255 }, { 0, 0, 0 }, 4, 200, 100,
										0 },  //subdome1
								{ 0x04, { 0, 0, 255 }, { 0, 0, 0 }, 4, 200, 100,
										0 },  //subdome2
								{ 0x04, { 0, 0, 255 }, { 0, 0, 0 }, 4, 200, 100,
										0 },   //subdome3
								{ 0x04, { 0, 0, 255 }, { 0, 0, 0 }, 4, 200, 100,
										0 },  //subdome4
								{ 0x04, { 0, 0, 255 }, { 0, 0, 0 }, 4, 200, 100,
										0 },  //subdome5
								{ 0x04, { 0, 0, 255 }, { 0, 0, 0 }, 4, 200, 100,
										0 },  //subdome6
								{ 0x04, { 0, 0, 255 }, { 0, 0, 0 }, 4, 200, 100,
										0 }    //subdome7

						}  //end dome0
				}  // end big dome0
		};

void app_dome_start(uint8_t index);
void app_dome_Init(void) {

	memset((uint8_t *) &subDome_Assist, 0, sizeof(subDome_Assist));

	strcpy(domeHeader.name, "HOME");
	domeHeader.number = 4;

	subDome.mode = 0x05;

	subDome.color1.R = 200;
	subDome.color2.R = 0;

	subDome.color1.G = 180;
	subDome.color2.G = 0;

	subDome.color1.B = 120;
	subDome.color2.B = 0;

	subDome.repeate = 30;
	subDome.bright = 90;

	subDome.speed = 3;
	subDome.offtime = 60;

	app_dome_start(0);

}

void app_dome_500ms_pro(void) {

}
uint16_t app_dome_get_status(void) {

	return 0;
}
void app_dome_stop_current(void) {

}
void app_dome_start(uint8_t index) {
	subDome_Assist.switch_flag = 0;
	subDome_Assist.msCnt = 0;
	subDome_Assist.stopTime = 50;

	memcpy((uint8_t*) &domeHeader, (uint8_t*) &dome_default[1].header,
			sizeof(domeHeader));

	memcpy((uint8_t*) &subDome, (uint8_t*) &dome_default[1].subdome[0],
			sizeof(subDome));

//	app_eeprom_get_dome_with_index(&subDome, index);

}
static uint32_t tmp = 0;
static uint8_t tmp_color = 0;

void app_dome_interrupter(void) {

#if 1

	if (subDome_Assist.stopTime) {
		subDome_Assist.stopTime--;
		return;
	}

	if ((subDome.repeate == 0) && (subDome.offtime == 0)) {
		return;
	}

	switch (subDome.mode & 0x0F) {
	case 0x03:  //shadow
	{
		subDome_Assist.msCnt++;
		if (subDome.color1.R < subDome.color2.R) {
			tmp = subDome.color1.R * 256
					+ subDome_Assist.msCnt * 256
							* abs(subDome.color2.R - subDome.color1.R)
							/ subDome.speed;
			tmp = subDome.bright * tmp / 100;
			Light_Red_set(tmp & 0xFFFF);
		} else {
			tmp = subDome.color1.R * 256
					- subDome_Assist.msCnt * 256
							* abs(subDome.color2.R - subDome.color1.R)
							/ subDome.speed;
			tmp = subDome.bright * tmp / 100;
			Light_Red_set(tmp);
		}
		//////
		if (subDome.color1.G < subDome.color2.G) {
			tmp = subDome.color1.G * 256
					+ subDome_Assist.msCnt * 256
							* abs(subDome.color2.G - subDome.color1.G)
							/ subDome.speed;
			tmp = subDome.bright * tmp / 100;
			Light_Green_set(tmp);
		} else {
			tmp = subDome.color1.G * 256
					- subDome_Assist.msCnt * 256
							* abs(subDome.color2.G - subDome.color1.G)
							/ subDome.speed;
			tmp = subDome.bright * tmp / 100;
			Light_Green_set(tmp);
		}
		//////
		if (subDome.color1.B < subDome.color2.B) {
			tmp = subDome.color1.B * 256
					+ subDome_Assist.msCnt * 256
							* abs(subDome.color2.B - subDome.color1.B)
							/ subDome.speed;
			tmp = subDome.bright * tmp / 100;
			Light_Blue_set(tmp);
		} else {
			tmp = subDome.color1.B * 256
					- subDome_Assist.msCnt * 256
							* abs(subDome.color2.B - subDome.color1.B)
							/ subDome.speed;
			tmp = subDome.bright * tmp / 100;
			Light_Blue_set(tmp);
		}

		if (subDome_Assist.msCnt >= subDome.speed) {
			subDome_Assist.msCnt = 0;

			tmp_color = subDome.color2.R;
			subDome.color2.R = subDome.color1.R;
			subDome.color1.R = tmp_color;

			tmp_color = subDome.color2.G;
			subDome.color2.G = subDome.color1.G;
			subDome.color1.G = tmp_color;

			tmp_color = subDome.color2.B;
			subDome.color2.B = subDome.color1.B;
			subDome.color1.B = tmp_color;

			if (subDome_Assist.switch_flag == 0) {
				subDome_Assist.switch_flag = 1;

			} else {
				subDome_Assist.switch_flag = 0;

				if (subDome.repeate) {
					subDome.repeate--;
				}
			}
		}
		if (subDome.repeate == 0) {
			Light_RGB_set(0, 0, 0);

			if (subDome.offtime) {
				subDome.offtime--;
			}
			if (subDome.offtime == 0) {
				app_dome_start(subDome.mode);
			}

		}
	}
		break;
	case 0x04:  //breath
	{
		if (subDome_Assist.switch_flag == 0) {
			subDome_Assist.msCnt++;
		} else {
			if (subDome_Assist.msCnt) {
				subDome_Assist.msCnt--;
			}
		}

		tmp = 0xFF * subDome_Assist.msCnt * subDome.color1.R / subDome.speed;
		tmp = tmp * subDome.bright / 100;
		Light_Red_set(tmp & 0xFFFF);

		tmp = 0xFF * subDome_Assist.msCnt * subDome.color1.G / subDome.speed;
		tmp = tmp * subDome.bright / 100;
		Light_Green_set(tmp & 0xFFFF);

		tmp = 0xFF * subDome_Assist.msCnt * subDome.color1.B / subDome.speed;
		tmp = tmp * subDome.bright / 100;
		Light_Blue_set(tmp & 0xFFFF);

		if ((subDome_Assist.msCnt >= subDome.speed)
				|| (subDome_Assist.msCnt == 0)) {
			if (subDome_Assist.switch_flag == 0) {
				subDome_Assist.switch_flag = 1;
			} else {
				subDome_Assist.switch_flag = 0;
				if (subDome.repeate) {
					subDome.repeate--;
				}
			}
		}
		if (subDome.repeate == 0) {
			Light_RGB_set(0, 0, 0);
			if (subDome.offtime) {
				subDome.offtime--;
			}
			if (subDome.offtime == 0) {
				app_dome_start(subDome.mode);
			}
		}
	}
		break;
	case 0x05:  //blink
	{
		uint32_t tt = 0xFF;
		if (subDome_Assist.msCnt == 0) {
			tmp = tt * subDome.color1.R * subDome.bright / 100;
			Light_Red_set(tmp & 0xFFFF);

			tmp = tt * subDome.color1.G * subDome.bright / 100;
			Light_Green_set(tmp & 0xFFFF);

			tmp = tt * subDome.color1.B * subDome.bright / 100;
			Light_Blue_set(tmp & 0xFFFF);
		}
		if (subDome_Assist.msCnt == (uint32_t) subDome.speed) {
			tmp = tt * subDome.color2.R * subDome.bright / 100;
			Light_Red_set(tmp & 0xFFFF);

			tmp = tt * subDome.color2.G * subDome.bright / 100;
			Light_Green_set(tmp & 0xFFFF);

			tmp = tt * subDome.color2.B * subDome.bright / 100;
			Light_Blue_set(tmp & 0xFFFF);
		}
		subDome_Assist.msCnt++;
		if (subDome_Assist.msCnt >= (subDome.speed + subDome.offtime)) {
			subDome_Assist.msCnt = 0;

			if (subDome.repeate) {
				subDome.repeate--;
			}

		}
		if (subDome.repeate == 0) {
			Light_RGB_set(0, 0, 0);
			if (subDome.offtime) {
				subDome.offtime--;
			}
			if (subDome.offtime == 0) {
				app_dome_start(subDome.mode);
			}
		}
	}
		break;
	default:

		break;
	}

#endif
}
