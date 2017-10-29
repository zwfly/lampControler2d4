/*
 * app_dome.h
 *
 *  Created on: 2017年9月8日
 *      Author: fly
 */

#ifndef APP_INC_APP_DOME_H_
#define APP_INC_APP_DOME_H_

#define DEFAULT_DOME_NUM   15

typedef struct _DOME_PRO_T {
	uint8_t currentDomeIndex;
//	uint8_t currentSubDomeIndex;

} DOME_PRO_T;

typedef struct _SUBDOME_ASSIST_T {
	uint8_t switch_flag;
	uint32_t msCnt;
	uint8_t stopTime;
} SUBDOME_ASSIST_T;
///////
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
//typedef union _REPEAT_NUMBER_T {
//	uint8_t datas;
//	struct {
//		unsigned repeat :4;
//		unsigned number :4;
//	} bits;
//} REPEAT_NUMBER_T;
typedef struct _DOME_HEADER_T {
	char name[8];
	uint8_t index;  //刚加的
	uint8_t repeat_number;  //闪法重复的次数，单元模式的数量
} DOME_HEADER_T;

typedef struct _DOME_DEFAULT_T {
	DOME_HEADER_T header;
	SUBDOME_T subdome[8];
} DOME_DEFAULT_T;

void app_dome_Init(void);

void app_dome_previous(void);
void app_dome_next(void);
void app_dome_get_current_Name(char *name, uint8_t len);
void app_dome_start_current(void);
void app_dome_stop_current(void);
void app_dome_interrupter(void);

#endif /* APP_INC_APP_DOME_H_ */
