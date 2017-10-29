/*
 * app_dome.c
 *
 *  Created on: 2017Äê9ÔÂ8ÈÕ
 *      Author: fly
 */

#include "app.h"
#include <stdlib.h>

static idata SUBDOME_T subDome;
static DOME_HEADER_T domeHeader;
static SUBDOME_ASSIST_T subDome_Assist;
static DOME_PRO_T domePro;
///////////////////

code const DOME_DEFAULT_T dome_default[DEFAULT_DOME_NUM] = {  //
		{ //start big dome0
				{  //start header0
						"    DOME", 0, 0x01  //header0 body
						},//end header0
						{  //start dome0
								{ 0x05, { 255, 255, 255 }, { 0, 0, 0 }, 1, 200,
										100, 0 }, //subdome0
								{ 0x14, { 255, 0, 0 }, { 0, 0, 0 }, 1, 200, 100,
										0 },  //subdome1
								{ 0x24, { 0, 255, 0 }, { 0, 0, 0 }, 1, 200, 100,
										0 },  //subdome2
								{ 0x34, { 0, 255, 0 }, { 0, 0, 0 }, 1, 200, 100,
										0 },   //subdome3
								{ 0x44, { 0, 255, 0 }, { 0, 0, 0 }, 1, 200, 100,
										0 },  //subdome4
								{ 0x54, { 0, 255, 0 }, { 0, 0, 0 }, 1, 200, 100,
										0 },  //subdome5
								{ 0x64, { 0, 255, 0 }, { 0, 0, 0 }, 1, 200, 100,
										0 },  //subdome6
								{ 0x74, { 0, 255, 0 }, { 0, 0, 0 }, 1, 200, 100,
										0 }    //subdome7
						}  //end dome0
				},  // end big dome0
				{ //start big dome1
				{  //start header0
						"     LSU", 0, 0x02 }, //end header0
						{  //start dome0
						{ 0x03, { 160, 32, 240 }, { 255, 165, 0 }, 1, 200, 100,
								0 }, //subdome0
								{ 0x13, { 255, 165, 0 }, { 160, 32, 240 }, 1,
										200, 100, 0 },  //subdome1
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
				{ //start big dome2
				{  //start header0
						"    XMAS", 0, 0x03 }, //end header0
						{  //start dome0
						{ 0x03, { 255, 0, 0 }, { 0, 255, 0 }, 1, 200, 100, 0 }, //subdome0
								{ 0x13, { 0, 255, 0 }, { 255, 255, 255 }, 1,
										200, 100, 0 },  //subdome1
								{ 0x23, { 255, 255, 255 }, { 255, 0, 0 }, 1,
										200, 100, 0 },  //subdome2
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
				},  // end big dome2
				{ //start big dome3
				{  //start header0
						"   MARDI", 0, 0x04 }, //end header0
						{  //start dome0
						{ 0x03, { 255, 0, 0 }, { 0, 255, 0 }, 1, 100, 100, 0 }, //subdome0
								{ 0x13, { 0, 255, 0 }, { 160, 32, 240 }, 1, 100,
										100, 0 },  //subdome1
								{ 0x23, { 160, 32, 240 }, { 255, 255, 0 }, 1,
										100, 100, 0 },  //subdome2
								{ 0x33, { 255, 255, 0 }, { 255, 0, 0 }, 1, 100,
										100, 0 },   //subdome3
								{ 0x44, { 0, 0, 255 }, { 0, 0, 0 }, 4, 200, 100,
										0 },  //subdome4
								{ 0x54, { 0, 0, 255 }, { 0, 0, 0 }, 4, 200, 100,
										0 },  //subdome5
								{ 0x64, { 0, 0, 255 }, { 0, 0, 0 }, 4, 200, 100,
										0 },  //subdome6
								{ 0x74, { 0, 0, 255 }, { 0, 0, 0 }, 4, 200, 100,
										0 }    //subdome7

						}  //end dome0
				},  // end big dome3
				{ //start big dome4
				{  //start header0
						"   FADE1", 0, 0x01 }, //end header0
						{  //start dome0
						{ 0x04, { 255, 0, 0 }, { 0, 0, 0 }, 1, 200, 100, 0 }, //subdome0
								{ 0x13, { 0, 255, 0 }, { 160, 32, 240 }, 1, 100,
										100, 0 },  //subdome1
								{ 0x23, { 160, 32, 240 }, { 255, 255, 0 }, 1,
										100, 100, 0 },  //subdome2
								{ 0x33, { 255, 255, 0 }, { 255, 0, 0 }, 1, 100,
										100, 0 },   //subdome3
								{ 0x44, { 0, 0, 255 }, { 0, 0, 0 }, 4, 200, 100,
										0 },  //subdome4
								{ 0x54, { 0, 0, 255 }, { 0, 0, 0 }, 4, 200, 100,
										0 },  //subdome5
								{ 0x64, { 0, 0, 255 }, { 0, 0, 0 }, 4, 200, 100,
										0 },  //subdome6
								{ 0x74, { 0, 0, 255 }, { 0, 0, 0 }, 4, 200, 100,
										0 }    //subdome7

						}  //end dome0
				},  // end big dome4
				{ //start big dome4
				{  //start header0
						"   FADE2", 0, 0x01 }, //end header0
						{  //start dome0
						{ 0x04, { 0, 255, 0 }, { 0, 0, 0 }, 1, 200, 100, 0 }, //subdome0
								{ 0x13, { 0, 255, 0 }, { 160, 32, 240 }, 1, 100,
										100, 0 },  //subdome1
								{ 0x23, { 160, 32, 240 }, { 255, 255, 0 }, 1,
										100, 100, 0 },  //subdome2
								{ 0x33, { 255, 255, 0 }, { 255, 0, 0 }, 1, 100,
										100, 0 },   //subdome3
								{ 0x44, { 0, 0, 255 }, { 0, 0, 0 }, 4, 200, 100,
										0 },  //subdome4
								{ 0x54, { 0, 0, 255 }, { 0, 0, 0 }, 4, 200, 100,
										0 },  //subdome5
								{ 0x64, { 0, 0, 255 }, { 0, 0, 0 }, 4, 200, 100,
										0 },  //subdome6
								{ 0x74, { 0, 0, 255 }, { 0, 0, 0 }, 4, 200, 100,
										0 }    //subdome7

						}  //end dome0
				}, // end big dome4
				{ //start big dome4
				{  //start header0
						"   FADE3", 0, 0x01 }, //end header0
						{  //start dome0
						{ 0x04, { 0, 0, 255 }, { 0, 0, 0 }, 1, 200, 100, 0 }, //subdome0
								{ 0x13, { 0, 255, 0 }, { 160, 32, 240 }, 1, 100,
										100, 0 },  //subdome1
								{ 0x23, { 160, 32, 240 }, { 255, 255, 0 }, 1,
										100, 100, 0 },  //subdome2
								{ 0x33, { 255, 255, 0 }, { 255, 0, 0 }, 1, 100,
										100, 0 },   //subdome3
								{ 0x44, { 0, 0, 255 }, { 0, 0, 0 }, 4, 200, 100,
										0 },  //subdome4
								{ 0x54, { 0, 0, 255 }, { 0, 0, 0 }, 4, 200, 100,
										0 },  //subdome5
								{ 0x64, { 0, 0, 255 }, { 0, 0, 0 }, 4, 200, 100,
										0 },  //subdome6
								{ 0x74, { 0, 0, 255 }, { 0, 0, 0 }, 4, 200, 100,
										0 }    //subdome7

						}  //end dome0
				},  // end big dome4
				{ //start big dome4
				{  //start header0
						"   FADE4", 0, 0x01 }, //end header0
						{  //start dome0
						{ 0x04, { 160, 32, 240 }, { 0, 0, 0 }, 1, 200, 100, 0 }, //subdome0
								{ 0x13, { 0, 255, 0 }, { 160, 32, 240 }, 1, 100,
										100, 0 },  //subdome1
								{ 0x23, { 160, 32, 240 }, { 255, 255, 0 }, 1,
										100, 100, 0 },  //subdome2
								{ 0x33, { 255, 255, 0 }, { 255, 0, 0 }, 1, 100,
										100, 0 },   //subdome3
								{ 0x44, { 0, 0, 255 }, { 0, 0, 0 }, 4, 200, 100,
										0 },  //subdome4
								{ 0x54, { 0, 0, 255 }, { 0, 0, 0 }, 4, 200, 100,
										0 },  //subdome5
								{ 0x64, { 0, 0, 255 }, { 0, 0, 0 }, 4, 200, 100,
										0 },  //subdome6
								{ 0x74, { 0, 0, 255 }, { 0, 0, 0 }, 4, 200, 100,
										0 }    //subdome7

						}  //end dome0
				},  // end big dome4
				{ //start big dome4
				{  //start header0
						"   FADE5", 0, 0x01 }, //end header0
						{  //start dome0
						{ 0x04, { 255, 165, 0 }, { 0, 0, 0 }, 1, 200, 100, 0 }, //subdome0
								{ 0x13, { 0, 255, 0 }, { 160, 32, 240 }, 1, 100,
										100, 0 },  //subdome1
								{ 0x23, { 160, 32, 240 }, { 255, 255, 0 }, 1,
										100, 100, 0 },  //subdome2
								{ 0x33, { 255, 255, 0 }, { 255, 0, 0 }, 1, 100,
										100, 0 },   //subdome3
								{ 0x44, { 0, 0, 255 }, { 0, 0, 0 }, 4, 200, 100,
										0 },  //subdome4
								{ 0x54, { 0, 0, 255 }, { 0, 0, 0 }, 4, 200, 100,
										0 },  //subdome5
								{ 0x64, { 0, 0, 255 }, { 0, 0, 0 }, 4, 200, 100,
										0 },  //subdome6
								{ 0x74, { 0, 0, 255 }, { 0, 0, 0 }, 4, 200, 100,
										0 }    //subdome7

						}  //end dome0
				},  // end big dome4
				{ //start big dome4
				{  //start header0
						"  SHARP1", 0, 0x01 }, //end header0
						{  //start dome0
						{ 0x05, { 255, 0, 0 }, { 0, 0, 0 }, 1, 100, 100, 100 }, //subdome0
								{ 0x13, { 0, 255, 0 }, { 160, 32, 240 }, 1, 100,
										100, 0 },  //subdome1
								{ 0x23, { 160, 32, 240 }, { 255, 255, 0 }, 1,
										100, 100, 0 },  //subdome2
								{ 0x33, { 255, 255, 0 }, { 255, 0, 0 }, 1, 100,
										100, 0 },   //subdome3
								{ 0x44, { 0, 0, 255 }, { 0, 0, 0 }, 4, 200, 100,
										0 },  //subdome4
								{ 0x54, { 0, 0, 255 }, { 0, 0, 0 }, 4, 200, 100,
										0 },  //subdome5
								{ 0x64, { 0, 0, 255 }, { 0, 0, 0 }, 4, 200, 100,
										0 },  //subdome6
								{ 0x74, { 0, 0, 255 }, { 0, 0, 0 }, 4, 200, 100,
										0 }    //subdome7

						}  //end dome0
				},  // end big dome4
				{ //start big dome4
				{  //start header0
						"  SHARP2", 0, 0x01 }, //end header0
						{  //start dome0
						{ 0x05, { 0, 255, 0 }, { 0, 0, 0 }, 1, 100, 100, 100 }, //subdome0
								{ 0x13, { 0, 255, 0 }, { 160, 32, 240 }, 1, 100,
										100, 0 },  //subdome1
								{ 0x23, { 160, 32, 240 }, { 255, 255, 0 }, 1,
										100, 100, 0 },  //subdome2
								{ 0x33, { 255, 255, 0 }, { 255, 0, 0 }, 1, 100,
										100, 0 },   //subdome3
								{ 0x44, { 0, 0, 255 }, { 0, 0, 0 }, 4, 200, 100,
										0 },  //subdome4
								{ 0x54, { 0, 0, 255 }, { 0, 0, 0 }, 4, 200, 100,
										0 },  //subdome5
								{ 0x64, { 0, 0, 255 }, { 0, 0, 0 }, 4, 200, 100,
										0 },  //subdome6
								{ 0x74, { 0, 0, 255 }, { 0, 0, 0 }, 4, 200, 100,
										0 }    //subdome7

						}  //end dome0
				}, // end big dome4
				{ //start big dome4
				{  //start header0
						"  SHARP3", 0, 0x01 }, //end header0
						{  //start dome0
						{ 0x05, { 0, 0, 255 }, { 0, 0, 0 }, 1, 100, 100, 100 }, //subdome0
								{ 0x13, { 0, 255, 0 }, { 160, 32, 240 }, 1, 100,
										100, 0 },  //subdome1
								{ 0x23, { 160, 32, 240 }, { 255, 255, 0 }, 1,
										100, 100, 0 },  //subdome2
								{ 0x33, { 255, 255, 0 }, { 255, 0, 0 }, 1, 100,
										100, 0 },   //subdome3
								{ 0x44, { 0, 0, 255 }, { 0, 0, 0 }, 4, 200, 100,
										0 },  //subdome4
								{ 0x54, { 0, 0, 255 }, { 0, 0, 0 }, 4, 200, 100,
										0 },  //subdome5
								{ 0x64, { 0, 0, 255 }, { 0, 0, 0 }, 4, 200, 100,
										0 },  //subdome6
								{ 0x74, { 0, 0, 255 }, { 0, 0, 0 }, 4, 200, 100,
										0 }    //subdome7

						}  //end dome0
				},  // end big dome4
				{ //start big dome4
				{  //start header0
						"  SHARP4", 0, 0x01 }, //end header0
						{  //start dome0
								{ 0x05, { 160, 32, 240 }, { 0, 0, 0 }, 1, 100,
										100, 100 }, //subdome0
								{ 0x13, { 0, 255, 0 }, { 160, 32, 240 }, 1, 100,
										100, 0 },  //subdome1
								{ 0x23, { 160, 32, 240 }, { 255, 255, 0 }, 1,
										100, 100, 0 },  //subdome2
								{ 0x33, { 255, 255, 0 }, { 255, 0, 0 }, 1, 100,
										100, 0 },   //subdome3
								{ 0x44, { 0, 0, 255 }, { 0, 0, 0 }, 4, 200, 100,
										0 },  //subdome4
								{ 0x54, { 0, 0, 255 }, { 0, 0, 0 }, 4, 200, 100,
										0 },  //subdome5
								{ 0x64, { 0, 0, 255 }, { 0, 0, 0 }, 4, 200, 100,
										0 },  //subdome6
								{ 0x74, { 0, 0, 255 }, { 0, 0, 0 }, 4, 200, 100,
										0 }    //subdome7

						}  //end dome0
				},  // end big dome4
				{ //start big dome4
				{  //start header0
						"  SHARP5", 0, 0x01 }, //end header0
						{  //start dome0
								{ 0x05, { 255, 165, 0 }, { 0, 0, 0 }, 1, 100,
										100, 100 }, //subdome0
								{ 0x13, { 0, 255, 0 }, { 160, 32, 240 }, 1, 100,
										100, 100 },  //subdome1
								{ 0x23, { 160, 32, 240 }, { 255, 255, 0 }, 1,
										100, 100, 100 },  //subdome2
								{ 0x33, { 255, 255, 0 }, { 255, 0, 0 }, 1, 100,
										100, 0 },   //subdome3
								{ 0x44, { 0, 0, 255 }, { 0, 0, 0 }, 4, 200, 100,
										0 },  //subdome4
								{ 0x54, { 0, 0, 255 }, { 0, 0, 0 }, 4, 200, 100,
										0 },  //subdome5
								{ 0x64, { 0, 0, 255 }, { 0, 0, 0 }, 4, 200, 100,
										0 },  //subdome6
								{ 0x74, { 0, 0, 255 }, { 0, 0, 0 }, 4, 200, 100,
										0 }    //subdome7

						}  //end dome0
				}, // end big dome4
				{ //start big dome4
				{  //start header0
						" GRADIEN", 0, 0x07 }, //end header0
						{  //start dome0
								{ 0x03, { 255, 0, 0 }, { 255, 0x7F, 0 }, 1, 100,
										100, 0 }, //subdome0
								{ 0x13, { 255, 0x7F, 0 }, { 255, 255, 0 }, 1,
										100, 100, 0 },  //subdome1
								{ 0x23, { 255, 255, 0 }, { 0, 255, 0 }, 1, 100,
										100, 0 },  //subdome2
								{ 0x33, { 0, 255, 0 }, { 0, 255, 255 }, 1, 100,
										100, 0 },   //subdome3
								{ 0x43, { 0, 255, 255 }, { 0, 0, 255 }, 1, 100,
										100, 0 },  //subdome4
								{ 0x53, { 0, 0, 255 }, { 0x8B, 0, 255 }, 1, 100,
										100, 0 },  //subdome5
								{ 0x63, { 0x8B, 0, 255 }, { 255, 0, 0 }, 1, 100,
										100, 0 },  //subdome6
								{ 0x73, { 0, 0, 255 }, { 0, 0, 0 }, 4, 200, 100,
										0 }    //subdome7

						}  //end dome0
				}  // end big dome4
		};

//////////////////
void app_dome_start(uint8_t index);
void app_dome_Init(void) {

	memset((uint8_t *) &subDome_Assist, 0, sizeof(subDome_Assist));

	memset((uint8_t *) &domePro, 0, sizeof(domePro));

	app_dome_start(0);

}
void app_dome_previous(void) {
	if (domePro.currentDomeIndex) {
		domePro.currentDomeIndex--;
	} else {
		domePro.currentDomeIndex = DEFAULT_DOME_NUM - 1;
	}
	app_dome_start(domePro.currentDomeIndex);
}
void app_dome_next(void) {
	domePro.currentDomeIndex++;
	if (domePro.currentDomeIndex >= DEFAULT_DOME_NUM) {
		domePro.currentDomeIndex = 0;
	}

	app_dome_start(domePro.currentDomeIndex);

}

void app_dome_get_current_Name(char *name, uint8_t len) {
	if (len > sizeof(dome_default[domePro.currentDomeIndex].header.name)) {
		name = 0;
		return;
	}
	memcpy((uint8_t *) name,
			(uint8_t *) dome_default[domePro.currentDomeIndex].header.name,
			len);
}
void app_dome_start_current(void) {

	app_dome_start(domePro.currentDomeIndex);

}
void app_dome_stop_current(void) {

	subDome.repeate = 0;
	subDome.offtime = 0;
	Light_RGB_set(0, 0, 0);

}
void app_dome_single_cycle(uint8_t subIndex) {
	if ((dome_default[domePro.currentDomeIndex].header.repeat_number & 0x0F)
			== (subIndex + 1)) {
		subIndex = 0;
		memcpy((uint8_t*) &subDome,
				(uint8_t*) &dome_default[domePro.currentDomeIndex].subdome[subIndex],
				sizeof(subDome));
	} else {
		memcpy((uint8_t*) &subDome,
				(uint8_t*) &dome_default[domePro.currentDomeIndex].subdome[subIndex
						+ 1], sizeof(subDome));
	}

	memcpy((uint8_t*) &domeHeader,
			(uint8_t*) &dome_default[domePro.currentDomeIndex].header,
			sizeof(domeHeader));

}
void app_dome_start(uint8_t domeIndex) {
	subDome_Assist.switch_flag = 0;
	subDome_Assist.msCnt = 0;
	subDome_Assist.stopTime = 50;

//	app_dome_single_cycle(domeIndex);

	domePro.currentDomeIndex = domeIndex;

	memcpy((uint8_t*) &subDome,
			(uint8_t*) &dome_default[domePro.currentDomeIndex].subdome[0],
			sizeof(subDome));

	memcpy((uint8_t*) &domeHeader,
			(uint8_t*) &dome_default[domePro.currentDomeIndex].header,
			sizeof(domeHeader));

}

static void app_dome_subDome_pro(uint8_t subIndex) {
	subDome_Assist.switch_flag = 0;
	subDome_Assist.msCnt = 0;
	subDome_Assist.stopTime = 0;

	app_dome_single_cycle(subIndex);

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
#if 0
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
#else

			if (subDome.repeate) {
				subDome.repeate--;
			}

#endif
		}
		if (subDome.repeate == 0) {
//			Light_RGB_set(0, 0, 0);

			if (subDome.offtime) {
				subDome.offtime--;
			}
			if (subDome.offtime == 0) {
				app_dome_subDome_pro(subDome.mode >> 4);
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
//			Light_RGB_set(0, 0, 0);
			if (subDome.offtime) {
				subDome.offtime--;
			}
			if (subDome.offtime == 0) {
				app_dome_subDome_pro(subDome.mode >> 4);
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
//			Light_RGB_set(0, 0, 0);
			if (subDome.offtime) {
				subDome.offtime--;
			}
			if (subDome.offtime == 0) {
				app_dome_subDome_pro(subDome.mode >> 4);
			}
		}
	}
		break;
	default:

		break;
	}

#endif
}
